<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

# 1. Lecture 2

## 1.1. Transferring data between NIC and end-host

To transfer data:

Strategy 1:

- CPU does polling of I/O controller (PIO: Special Instructions - cpu has to specifically issue special instructions or Memory-mapped IO - aliases are mapped to memory directly, and cpu does not know that it is)
- CPU does data copy

Cons: waste of cpu cycles, ..

Strategy 2:

- DMA - direct memory access (program - data transfer happens there, data copy)
- Interrupts (notify)

Cons: ----

Interrupt: ----

1. devices raises interrup req
2. processor interrupts program in execution
3. interrupts are disabled
4. device is informed of acceptance and, as a consequence, lowers interrupt
5. ......
6. .........
7. .........

There are a ton of interrupts (interrupt per packet). \
That is why there can be _interrupt storms/livelocks_, where there are more interrupts than progress can be made. (interrupt -> cpu starts processing -> another interrupt comes -> ...)

How to mitigate Interrupt storms:

1. Interrupt coalescing - don't generate interrupt on every packet, but on n packets; or choose a typical value
2. Polling - disable interrupts, and use cpy polling to check for new packet arrivals
3. do a hybrid - e.g. interrupts -> polling -> interrupts. (ethtool -c)

### 1.1.1. Building packets with headers and trailers

We do not know the header sizes \
e.g. TCP layer does does not know IP layer packet size.
So it is hard to know what memory to allocate since it has to be contiguos with our memory.

Scatter Gather I/O: \
instead of one address, one length, pass a list of addresses if length to the DMA engine.

### 1.1.2. Unit of processing

Application --send() max 2^(64-1) bytes allowed-->

Networking Stack -> 1GB/1500 = ~64k packets or 1GB/64KB = ~16K packets with large TCP/IP packets.

Network Interface Controller (NIC) -> packet (2^16 Bytes) in IP -> Frames (576 Bytes MTU - maximum transmition unit)

Small MTU:

- more multiplexing, fine graned transmission
- BUT inefficiency

Big MTU:

- ........
- .......

Ethernet MTU: 1500 Bytes
Preable 7 + SFD 1 + Ethernet Frame up to 1518 + Inter packet gap (12)

Preamble - is a like a marker that the shared medium is being used.

Ethernet Frame: dst mac 6 + src mac 6 + type 2 + Payload 1500 + crc 4

Payload: IP hdr 20 + TCP hdr 20 + payload 1460

Ethernet is a shared medium, which means that if packets collide, both are lost.

max efficiency 94.93%, thus max bandwidth 949.3 Mbps on 1Gps link

JUMBO frames. Most common 9000 bytes. so with this 99.14% efficiency. (slide 38). _9000 MTU is common in data centers, whereas 1500 is common on Internet. Because there has to be memory to buffer these frames._

IP does fragmentation

TCP does segmentation because it has sequence numbers and it is even easier to do that.

After TCP packet segmentation NIC, chops it up to MTUs.

TCP offloading: con - together with socket TCP offloading cannot do stateless, which means NIC has to keep the state of seqs and packets.

# 2. Lecture 3 - Linux Networking

## 2.1. Device interfaces

Between NIC <-> Device Driver - producer/consumer communication. The implementation is circular queues/rings of memory buffers. \
Producer (NIC does DMA) will add new buffers and consumer (Network stack) processes those buffers and unlinks them.

### 2.1.1. Receive path

1. packet received (network card)
2. DMA to memory using ring buffer addresses
3. raise an interrupt from (network card)
4. run IRQ handler
5. network device handler
6. NAPI (new API) schedule

**NAPI**: is the implementation of interrup mitigation technique. \
How it works: it will check if NAPI is already scheduled. \
NAPI processing: interrupts on NIC are disabled; process certain number of packets in one go; poll the device drivcer to check if there are more packets ready for processing; if not enough packets are available, then yield.

Software IRQ (interupt request)

processing NAPI:

- interrupt handling is a high priority work
- all further interrupts are disabled (which means that more coming packets will be missed and if the ring overflows - the packets are dropped)
- many long events in the incoming packets\
  Because of this, there are **SoftIRQs** in Linux kernel (_Bottom-Half Processing_). This allows most of the protocol processing while having interrupts enabled, thus can preempt other kernel threads, user processing.

The normal interrupts are handled in the _Top-Half Processing_. This is ISRs (_Interrupt Service Routines_). This is very high importance but also very small processing. Mostly concerned with cleaning hardware registers and copying out pointers,

**SKB - Socket Kernel Buffer** - one of the most important data types in Linux kernel. Represents a data packet in processing. Has headers, trailers, data, metadat, etc... \
Logically it contains Link list pointers, which network device needs to be transmitted to, which socket it needs to go, place for headers/trailers ofr various protocols, various Linux-specific accounting and reference counting info.

### 2.1.2. Send Path

Sending is synchronous so there is more control over it, rather than receiving side, which is asynchronous and is not controlled when the reception of the packet, interrupts, timeouts happen.

1. Queue data when application calls send()
2. Perform data packet building (TCP header, IP header, which device)
3. Tell the device driver to transmit the packet
4. Packet is transmitted on the network

**Stateless Offloading** - there is not state that a processing element needs to remember, each packet can be processed independently.

- checksum offloading, TSO offloading (LRO, GRO offloading)
- stateless offloading in hardware (or in driver software also possible)
- often is a performance optimization
  **Stateful offloading** - what you do with the current packet depends on some state that needs to be maintained.
- it is a correctness issue

### 2.1.3. **Overheads**

**Per-packet operations**

- generation of TCP/IP packets
- allocation of SKB structure
- TCP state machine transition
- ACK generation
- Queue management

Optimization examples: Jumbo packets, TCP segmentation offloading (TSO), Large Receive Offload (LRO)

**Per-byte operations**

- data copies
- checksum generation
- DMA
- IPSec (encrypt/decrypt)

Optimization can be offloading, scatter-gather IO capabilities.

# 3. Lecture 4 - Multicore Scalability

Dennard Scaling - observation that as the the transistor area decreases, frequency can increase, but there is a limitation in leakage current.\
This means that Moore's law stalled, and that is why multicore era started.

Ethernet speeds area still growing exponentially.

Multicore problem: if interrupt comes, there are multiple CPUs that are contending and locking each other out of the packet. _Solution_ could be using counters for each CPU, such that they can have read lock to these counters and get separate write locks. \
**Problem**: invalidation of cache lines - if the writes are close together, the caches will be invalidated. Also this is known as _cache ping-pong_. (Cache line is 64bytes long in x86).\
_Solution_ - padding caches, but this is not ideal that usually closely written things are accessed together (e.g. TCP packet)

1. Which of the CPU should get the intrrupt?\
   Typically the cpu0 is what gets all the interrupts. The reason for this is because cpu0 is an important role which, for example, wakes all other CPUs on boot.

Interrupt balancing \
_irqbalance_ - it will assign the interrupt to different cores such that the load is balanced. \
There can be specific mappings, such as static vs dynamic, affinity, !affinity, or manual pinning.

This idea is not ideal, because even if the load is balanced, it does not necessarily mean that you are keeping the connection state, last information, etc.

2. Which of the interrupts should receive on a single queue?\
   Interrupts are usually associated with an action (send/receive)\
   _Solution_ - Multi-queue NIC, which can have multiple RX/TX rings, which ideally would be per CPU.

3. Which packet go to which queue (in the NIC)?\
   Distribute by the part of the header, for example, by the port number.

Strategy 1: Random assignment. But packets from different connections will end up in different CPUs. Pros - simple and easy to implement, load balanced at the packet-level. Cons: cache polution and no connection management

Strategy 2: Receive Side Scaling (RSS) - CPU will have a connection that it is taking care of. This strategy is based on source ip, port, etc. This design raises a question if this does not invalidate the multicore processing, since the connection per CPU. However, even though UDP processing is possible parallelized, TCP is very hard because of sequence numbers, acks, and connection state.\
This is stateless offload because it does not depend on the previous packet. The hash is ip addresses + port numbers % number of queues.

RSS advantages:

- early decision on which cpu processing should be - early multiplexing
- cache locality
- ...

If you don't have this kind of NIC hardware, this can be done in the interrupt handler with softirqs. - this is **Receive Packet Steering (RPS)**

4. Application processing - applications can be scheduled on any core whre they call recv(), they can be moved around as well.\
   _Solution_ - Receive Flow Steering (RFS) - it will move around the connections and lookup the flow table for the active connections.

Transmit Packet Steering (XPS) - answers which trabsnut queue to choose to transmit a packet.\
often it is preferable to have RX queue with TX queue together on the same core, especially for TCP. This makes it easier for packet processing.

# 4. Lecture 5 - Userspace Networking Stacks

_What is packet processing?_ - it is a separate applications, middleware that work on raw network packets. E.g. firewall, routers, forwarding, load-balancers. These devices are not considered programmable, since they are concerned to run a single protocol very fast.

Key problem - Getting fast Access to Packets:\
typical solutions:

1. Raw sockets (AF_PACKETS) - but they have high overheads, packet copies, per packet sys . (they are fine for thousands, but not for millions packets per sec)
2. Packet filter hooks (eBPF)- but it is complex, in the kernel (does not give full-fledged access to the whole packet), limited changes.
3. Direct buffer access - but is run in the kernel, and PF_RINGS - data copies and shared metadata overheads.

**The root cause of high overheads**

1. Packet representations are very general, thus cause overheads
2. System calls are not cheap - they trap into the kernel, disrupt ongoing processing, processing ring switch, security checks.

## 4.1. Netmap optimizations

1. Better packet buffer management: \
   all uniform packet - fixed size to 2KB\
   a pool of them are initialized at the boot time and shared between NIC and application\
   multiple queue NICs - per core mapping, where each queue has its own file descriptor and memory
2. Give direct and safe access to NICs TX and RX queues:
3. Batched syscall processing:

It uses zero-copy stack, which is designed such that raw packets are built and transmitted directly from the user space.\
This is memory mapped IO, therefore NICs must be modified to support this.

What has netmap changed:

- brought attention to per-packet processing
- shown benefit of a) pre-allocating number of buffers, b) doing system call batching c) flexible user space packet processing implementation

User space - _why_:

- modern OS kernels are very complex, so it hard to add something or to maintain.
- kernel is very strictly regulated (Tannebaum-Torvalds debate which is better - micro-kernel or monolithic design).
- kernel has to reliably run anything from micro-controllers, cameras, etc
- no security leaks, multiple users,
- any processor or memory architecture for the next 10-30 years.

User space application don't necessarily need kernel permissions.\
E.g.: tunneling, VPN, tethering, encryption, TORing;\
cloud-computing, content distribution networks.

Netmap challenges:\
it is still integrated in linux kernel so needs to support ioct calls, polling etc\
needs to support many different NICs

DPDK framework - Data Plance Development Kit (started by Intel)

- Data path - code path where the actual work is done (try to make it straight forward, no blocking callsm everything is ready to go, everything is amortized)
- control path - code where the resources are managed
- fast path - common case execution (typically few branches, very simple code) - e.g. the next TCP packet is a data packet in estimated state in order, no special flags
- slow path - more sanity checks (more branches, so poorer performance) - e.g. TCP packet with URG and PSH flag set

Architecture:\
direct user space packket processing - completely eliminating the kernel. This is done by mapping the driver, IO, etc, completely in uspace.\
No device modifications are needed, and this is completely set up on polling, so no interrupts.

Key ideas:

1. No syscalls or interrupts - all polling
2. no kernel overheads in the data path
3. Multiple libraries and mechanisms supporting multicore affinity, buffer management, etc.

Why polling is the only option when hybrid is the best? - They can only do polling, because interrupts are not possible. The packets have to be in the design of DPDK.

Practical scenario - switching; use in the datacenters, where the overhead in the networking stack. I.e. scenario where it is expected to push the boundaries of the processing power.

### 4.1.1. mTCP: Scalable User Space TCP Stack

It is highly scalable uspace stack. \
Comaprison to megapipe: it has to do multicore scalability; new radical API (limit of megapipe); no kernel modification\
_Why user space?_ - Expensive syscall; Metadata/data copies; Kernel environment; Generality vs specialization arguments

What is it solving?:

- locality - split processing among cores
- shared fd space - decouple fds
- inefficient packet processing (netmap)
- syscall overheads (batching)

mTCP ideas:

1. TCP stack implementation in uspace (flexibility and easy of development and use, specialization of TCP - common option and fast path)
2. Leverage packet processing frameworks
3. Multi core scalability - per application thread desing and transparent batching of events and packet IO

mTCP:

1. can there there be zero-thread TCP model? - no, because there cannot be no active threads in the TCP.
2. Unique way they did TCP - they have 3 separate queues for control, ACK and data packet transfers. And had priority to the control (SYN/SYNACK) packets for transmission order.

They optimized fast lanes such that they fall in the same cache lines, thus reducing latency.

Significant performance improvements over previous efforts.\
Milestone work - proof of concept of an efficient TCP stack in uspace.

# 5. RDMA Networking

Latencies

This was not important when the Moore's law was improving all the systems.

However, it became important, when the speeds in the network are still growing, but the improvement in processing slowed down.

There is infiniBand networking stack, which is a full alternative to Eth/IP/TCP stack, which latencies are in 600nanoseconds sizes.

In 2011 paper _It's Time For Low Latency_ it shows how little improvement RTT (Round trip time) has compared to other improvements (Net Bandwithc, CPU to disk, etc)

Things to consider with latencies (to improve to 1us):

- Speed of light (rule of thumb is 5ns/m) (so it makes the square of 14x14m)
- Density of computation, power delivery, cooling (packing the server into the small square)
- Computation diameter
- Amount of data you can access

**Latency imprortance**:

- Micro services are important - 100-200 requests per page load for Amazon
- Latency sensitive workloads - big data processing, graph processing, streaming
- scientific workloads - high performance computing - weather simultation, genomics; and small caluclations + data access (this discussion was started by RAMclouds)

It looks quite bad, because switch (1us) + NIC (1us) + OS processing (5-6us) + speed of light (5-6ns) - makes it ~76% fault of OS.

How does socket contribute to it:

- socket is an application-level interface
- its simplistic design restricts many optimization opportunities
  - it is tied to the OS process abstraction with the file address space
  - OS decides on behalf of process when to write to DMA, when to copy, etc
- hard API integration

## 5.1. RDMA

It is a networking ..... (slide 15)

**Idea 1 - User-space networking** - Let the process manage its networking

**Idea 2 - Kernel Bypass** - Access hardware/NIC resources directly

New abstraction - data transmition (data operation) is not checked by the kernel (after the first time, because the first time it does check), which is a big optimization.

For control operations, there is a kernel check. Example - allocate needed memory, manage buffer, schedule process if necessary...

Together:

1. Allocate memory buffers (through kernel)
2. Allocate data and control queues (through kernel)
3. recv a message (directly)
4. get completion notification (directly) - this is not an interrupt because it would go through OS, so it is done with polling. For polling the app needs to be scheduled, and usually it is still scheduled because packets come in in order of us, where scheduling is around ms.
5. close (through kernel)

New RDMA Objects:

- Memory buffers
- Connection send/receive queues
- Control queues

Network IO happens by posting work requests (WRs) in the QP\
it contains - buffer, length\
and it processes .... (slide 28)

RDMA architectural view:

1. CLient: READ remote memory address raddr to local address laddr
2. Client: posts READ request
3. Server: read local raddr - local DMA operation
4. Server: TX data back to client NIC
5. Client: local DMA to laddr buffer in DRAM
6. ..........

it is a very powerful idea - no remote application/os/cpu involvement in data transfer.

Once you have capability to access remote memory from network you can imagin doing a lot of things like atomics or transactions\
Not limited just to sustem DRAM, think of DRAM in the GPU or even directly storage. - This is kinf of pretending that the memory is from your machine, not from network.

This was exactly what was done in Berkely, Stanford, etc even in the 80s-90s

## 5.2. Challenges with RDMA

- Debugging
  - operation failed, connection down, what went wrong?
  - logging and introspection can be hard
- Performance
  - Takes a while to get used to the new way of writing code - event driven, lots of resources
  - performance isolation
- Fragility
  - in the cloud
  - correctness and verification
- Scalability
  - how many concurrent socket connections can you support in your server?
  - how many memory buffers an RNIC can remember?

# 6. Network infrastructure

Handling connections:

- Circuit switching - each connection has its own circuit
- Packet switching - single circuit and data is built up of many smaller packets

Connecting two hosts - put data into frames (in link layer), send it over the digital signals, and take the data from frames.

## 6.1. Link layer\*\*

It is responsible over framing, error detection and medium access control (to avoid or detect connections).

Network node - any device that runs over the network (switch, pc, etc)

### 6.1.1. Framing

Byte oriented protocols (each frame as a collection of bytes). Widely used point-to-point protocol

Bit oriented protocols (each frame as a collection of bits). High level data link control protocol. Has bit-stuffing - sender inserts a 0 after seeing 5 1s.

Clock-based framing - synchronous optical network (SONET). Synce uses the first 2 bytes (with a pattern) in the overhead, look for pattern every 810 bytes, no bit stuffing.

### 6.1.2. Error detection

Detect errors in frames using redundant bits and discard the frame if an error is found.

Ways to check for errors:

- Parity checks (does not detect even amount of errors if in line, does not detect rectangles if 2d array)
- Checksums (adds all data, does 1s-complement, adds to the header, sends it; when received sums everything, and if it is 0, no errors are detected)
- Cyclic Redundancy Checks (CRC) - used by ethernet. Polynomial calculation

**End-to-end argument** - if the system is incorrectly implemented, there can be faults anywhere inside, therefore only the end points are the ones that can know if the communication was successful. This is the reason why in each layer there is some kind of error detection.

### 6.1.3. Collisions

If there are more than two computers connected to the bus, there is a high risk to have collisions of packets.

**Multiple access protocol** - its principles are work conserving, fairness, decentralized, simple.

## 6.2. Ethernet

At first it was hubs which just repeat the signal to all ports except the source, and needed the collision detection, because there can be multiple senders to one end point.

Now, in switches, the collision detection is not used because switch multiplexes and buffers signals in itself.

MAC addresses. Switches do not need the MAC address because it is transparent to all devices.

Ethernet frame structure:

- Destination MAc (6 bytes)
- Source MAC (6 bytes)
- Ethenet Type (2 bytes) - is decided by MTU
- Frame check sequence

Ethernet efficiency calculation: \
Protocol overhead = (packet size - payload size )/ payload size\
Protocol efficiency = payload size / packet size\
Ethernet efficiency = 1500 (or 1460 excl TCP/IP headers) / (1500 + 7 + 1 + .. +12) = 97.53%

Link layer switches - they forward/broadcast/drop frames based on the switch table and operate transparantly.\
It uses self-learning - every time a new device sends something, the switch saves the MAC address to the table. If the dest address is not found in the table, the data is broadcasted.

Types of switches:

- store-and-forward - everytime packet is passed through, it is buffered and only full is forwarded to the dest
- once the lookup is done, packet receiving and sending happen at the same time (pro: fast, con: if there are errors in the packet, CRC calculation cannot happen until it is fully received)

How to obtain the dest MAC address?\
Broadcast and get back their address.

A network of switches problems: the packets can loop; initial broadcasts will produce a big unnecessary load on the network.

- Flooding the network with loops - _solution_: build a topology without loops (tree topology). In practice, this is done with distributed spanning tree protocol.
- Traffic isolation - _solution_: VLAN - all the ports in the same VLAN will be broadcasted to, while ports on different VLANs are routed through an internal router within the switch. This adds additional 4 bytes in the eth hdr, which is for Tag Protocol Identifier (2 bytes), and Tag Control Information

Problems with switched Internet:

- broadcast storm - ARP requests, MAC addresses that have not been learned
- limited switch forwarding table
- limited isolation with VLAN (max 4096)
- security issues - packet sniffing, ARP spoofing attack, MAC flooding attack.

## 6.3. Network layer and routing

Router connects different networks.

**Control plane**: running protocols to figure out the path between one end to another end.

**Data plane**: packet forwarding with the match-action model (match on IP prefix table and do respective action)

Network layer addresses - IPv4/v6 (it is built from network identifier (IP prefix) + host identifier or network identifier + subnet identifier + host identifier)

IPv4 packet format (important parts):

- TOS - type of service, 2 bits reserved for Explicit Congestion Notification
- total length (typically bounded by MTU)
- Time to Live - avoid the loops in the network (each hop -1)

Journey of a packet:

1. check the dest IP address in the routing table (same subnet send a frame containing the packet to the dest IP with MAC; not same - send to the router with the gateway MAC)
2. in the router check the Ethernet MAC, lookup the IP prefix and take the correct action to the correct route.
3. forward the same process in the next.

All the routers need some processing to complete the routing algorithm protocols such that they complete the tables.

### 6.3.1. Router architecture

Two general functions:

- Routing - run routing protocols/algortithms to generate forwarding tables
- forwarding - make decision according to the packet data

For input port, There is a special hardware for the prefix matching - **TCAM (ternary matching)**

Switching fabric needs to be as fast as possible, and different ways of doing it are: memory bus (limited throughput), memory (memory bandwitch limits it), crossbar (non-blocking performance).

Head Of Line blocking - the one behind some other packets that are waiting is being blocked if they can just go. _Solution_ - virtual packet queue

Output port - it needs to buffer the packets such that it makes the frames with full information, and needs to do scheduling (FIFO queue, weighted fair queues, priority queues).

# 7. Congestion control

TCP guarantees reliability:

_stop-and-wait reliability_ - it is not really efficient because packets need to wait for a while

_unACKed data - packets in flight_ - this is more efficient; (this needs to track what packet is in-flight). \
Window in this case is a window of sequence numbers that have not been ack'ed. In this case if a segment has been received, the window can slide further and send out next packet.

Identifying dropped packets - suppose 4 packets are sent and one of them is dropped. What does the receiver do?

Strategies:

1. Go back N - don't ACK subsequent segments
2. Cumulative ACK - ACK subsequent segments and put last packet seq in order
3. Selective ACK - does ACK and puts the seq ranges that went there

TCP is trying to have connection as fast as possible but not faster. The idea is to allocate resources evenly and fully, but it is hard to do so in a decentralized manner. To do so, it can use packet conservation - keep the maximal packet amount in the network, and no new packet goes in until the old packet leaves the window.\
To do this, you can find the slowest bottleneck in the connection, which can be done with send and recv, and then send packets spaced out based on the slowest link. Then the equilibrium is reached.

How to reach the equilibrium quickly - TCP idea: _slow start_

How to adapt to the available space in the path accordingly - _sliding window mechanism_

### 7.0.1. TCP slow start

for every ACK you get, you send as many as the ACKs you got. (exp growth - 1, 2, 4, 8...) the window size is min(congestion windown and recv window)\
do that until packets start dropping - then restart and remember the max window size, and half of max.

how long does it take to reach a window of size W with slow-start - R\*logW

TCP AIMD - in the begining TCP does slow-start and then after first reset, do slow-start until half of the max congestion window and then do additive increase until the max.\
optimization of this is making the reset just to half of max cwindow and then doing additive increase from there (do not re-enter slow-start).

Problems with this:

1. will the queue always drain if we half the sending rate? - not guaranteed, because it is dependant on buffer and bandwith control protocol
2. How long does it take to ramp up?

why the packet could be dropped: buffer, bandwith delay pockets

# 8. HALF OF THE LECTURE WAS MISSED, GO BACK TO SLIDES

# 9. Software defined netowrking

There are a lot of artifacts because networking is complex.

Networks run in a distributed and autonomous way and scalability is important. With more functionalities (for different layers) together add complexity, and even though there are existing innovations, they are poorly adopted (e.g. IPv6).

Take a different look into network: \
There are two planes:

- Control plane - like a brain which runs distributed protocols how to do routing
- Data plane - like a set of rules for the scenatio (match-action table).

Netork planes on routers:

- Data plane is in line card and switch
- control plane is the processor in the router

**Complexity in the control plane**:

Control plane needs to achieve goals such as connectivity, inter-domain policy, isolation, access control, etc.

There are many mechanisms/protocols/

- globaly distributed - routing algos
- manual/scripted config - access control lists, VLANs
- Centralized computation: traffic engineering (indirect control)

Even worse, these mechanisms/protocols interact with each other - routing, addressing, access control, QoS

Say there are 2 regions, which both have data centers and both have clients. And you want to block cross-region traffic (client connects to the local data centre). Connect to the local routing's Access Control List and insert the list for specific ports. \
But say there is a link added to those closest routers to data centres, which actually breaks this traffic configuration, because there is a new path between the regions, thus ACLs need to be updated. \
This example shows that one improvement (connectivity) might break other mechanisms (ACL).

_The ability to master complexity is valuable but not the same as the ability to extract simplicity_ - you want to hide the complexity through levels of abstractions.

An example of this is programming. \
Machine languages don't have abstractions, but high-level languages are abstractions of them.

In networking the abstractions are layers. But this is just for data plane.

Abstractions for the control plane don't exist. There is no modularity that can be reused in other mechanisms, therefore networking seems like it is mainly about artifacts/engineering.

Goal is to program the network like the computers.

## 9.1. SDN ideas and abstractions

Some history: \
First attempt to make networks programmable was demultiplexing packets to software programs (active networking). This was done by inserting a snipet of code into the packet header, router would extract it and would apply the behaviour. Or the other way is to inject some code into the router before the packet. \
Evolution from that was separation of control/data planes. Example: Ethane - flow-based switching with centralized control for enterprise.

**Software defined network** - take the control plane and separate it from the data plane. Also centralize the control plane that would control several forwarding devices.

With this concept there can be a network arch, where data plane has boxes that is taking care only of data plane, but they have control channels to the centralized control network OS running control programs.

To realize this we need:

1. Abstraction for general forwarding model - for the communication between data plane boxes
2. Abstraction for network state - network OS should see a state or a representation rather than seeing those physical devices (running dijkstra on graph, not asking each box to compute their representation each)
3. Abstraction that simplifies configuration - not knowing the details of the topology, just knowing features of the traffic/topology. Does not care about the implementation, but about functionality

**Abs#1** \
Interface between forwarding blocks and network OS. This does not care about the way the match+action is implemented, but cares that it works. \
OpenFlow is current proposal for forwarding: standardized interface to switch, configuration in terms of flow entries, and no hardware modifications needed. Specifies how the OpenFlow switches communicate with network OS and vice versa. Match+action is great because by specifying any type of header to match on, any actions (that are supported) can be taken \
Benefits of this - switches are much cheaper, and no vendor lock-in

**Abs#2** \
Gives global network view - annotated network graph provided through an API. Control program: Configuration = Function(View) \
Implementation: "Network Operating Systems". Runs on servers in networks as controllers. Replicated for reliability. \
Information flows both ways - information from routers/switches to for the view and the configurations to routers/switches to control forwarding.

**Abs#3** \
Control mechanism expresses the desired behaviour. (e.g. isolation, access control, QoS) \
It should not be responsible for implementing that behaviour on physical network infrastructure - this requires configuring the forwarding tables in each switch. \
Proposed abs - abstract view of the network.

So far it is assumed that all the nodes are under the same authority. In between the authorities the BGP algo is run.

## 9.2. SDN use case - network slicing

**Network testing** - it is an interesting problem because it is hard to show that the new solution works. \
Solutions for that is to have a hardware testbed (but it is expensive and small scale because of NetFPGA), software testbed (can be large-scale (emulation), but performance is slow (CPU-based), no realistic topology and hard to maintain, wild test it on the internet (convincing network operators to try something new is very hard)). \
Therefore network testing is very problematic.

One _solution_ - **network slicing**.

Divide the production network into logical slices - one for production traffic and one for testing. \
Each slice/service controls its own packet forwarding (one is traditional and one is testing something new) \
And let users tot choose witch slice controls their traffic (this gives testing possibility and lets users experience something new) \
Existing services run on their slice as backup

There has to be a strong isolation between slices!

Allow the logical testbed to mirror the production network.

_Problem_ - in order to create slicing, you need to modify each and every router/switch to support one or another slice.

However OpenFlow interfaces has control mechanisms abstractions such that you don't need to modify switch, but add a FlowVisor intermediate entity which decides on slicing logic and then forward the control instructions from respective controller.

Slicing policies - each slicing policy can specifiy the resource limit for each slice: link bandwtich, max number of forwarding rules, topology, fraction of switch/router CPU. \
Also needs to have FlowSpaces - which packet does the slice control? - maps packets to slices according to their "classes" defined by the packet header fields.

Real user traffic - opt in \
Bob's experimental slice: all HTTP traffic to/from users who opted in (allow: tcp_port=80 and ip=user_ip) \
Alice's production slice: complementary to Bob's slice (Deny: (everything that Bob allows)) \
Monitoring slice that analyses all the traffic

FlowVisor packet handling:

1. packet-in exception from router to FlowVisor
2. Forward rules to the controller according to the packet
3. Generate the rules and check if the rules are exactly applicable

## 9.3. Data plane

OpenFlow - uses match+action abstraction - set of header match fields and forwarding actions. There is a list for all possible matches and possible actions. However, most hardware switches only support limited match/action set. And also it does not have everything to match on, thus the switch can only process protocols that it knows and it will ignore this header.

To have your own packet detected, ASIC (hardware) needs to be modified. But this takes years before the hardware gets delivered.

The main problem with this idea (new header not supported) is the **bottom-up mentality**.

However, there is a possiblity - make ASIC programmable and let new features be supported. To achieve this, there needs to be programmability supported on the CPU.

### 9.3.1. Programmability

Thus in networking there is a language created **P4**, which has its own data plane abstraction - **RMT**.

RMT is a RISC-inspired reconfigurable match tables model.

P4 is a domain-specific language for programming protocol-independent packet processors.

**RMT**: \
when packet comes in, it goes through "filter" like process to get the packet headers. These filters will need to specify what to match on and which action to take. After going through all the matches, packet is reassembled and sent out.

Applications of this: congestion control or in-network computing.

# 10. Data centers

## 10.1. Data center network arch

How to connect servers in a data center so that it has best throughput and performance?

1. have a giant switch, but has problems
   1. Switch would get overloaded (throughput), ie would interrupt signals and block
   2. single point of failure
   3. every time switch does not know where to send the packet, it will broadcast and thus network will be flooded
   4. even having found the ip addresses, there still need to be ARP packets sent
   5. isolating the traffic is hard
   6. limitted port density (there can be thousands of servers but no such switch)
2. Multiple switches and interconnecting them. (topologies can be line, bus, mesh, fully connected, tree, start, etc). Different topologies offer different trade-offs. The goal is to have a good connectivity but also lower complexity. Thus tree seems like it has a good connectivity and not that hard to build.

### 10.1.1. Tree-based data center network

Tree (but multi-rooted) is good to have such that it would have a good connectivity and low complexity. Multiple roots allow to avoid a single point of failure and better connectivity. \
Going from bottom to up, there need to be better (higher bandwith) switches installed, because there is more traffic. \
Problem of this design is that you cannot evolve the switches in a natural way, because of the hierarchical structure (upgrade lower layers, and then the upper layers need to be updated).

### 10.1.2. Network performance metrics

Bisection width: minimum number of links to cut to divide the network into two halves

Bisection bandwith: the minimum bandwidth of the links that divide the network into two halves

Full bisection bandwidth: nodes in one half can communicate to the other half in this bandwidth (?)

### 10.1.3. Oversubscription ratio

Ratio of worst-case required aggregate bandwidth to the total uplink bandwidth of a network device. - Ability of hosts to fully utilize its uplink capabilities.

Oversubscription ratio 1:1 means that all hosts can use full uplink capacity.

## 10.2. Factors behind data center network designs

Commoditication in the data center: \
inexpensive, commodity servers and storage devices \
the network is still highly specialized (using large-fanout proprietary switches)

Data center is not a "small internet" \
One admin domain, no firewall, limited policy routing, etc

Bandwidth is often a bottleneck \
Data-intesinve workloads (big-data, graph processing, etc) \
Low traffic locality, and the goal is to have flat high bandwith (pick random pair in the server, and the goal is to keep the same bandwidth between any nodes)

### 10.2.1. Fat-tree

to accomodate these factors - expand the tree topology to "fat-tree", which is a normal tree network, but has more linkst to the higher layers to improve the connectivity.

Goal is to achieve equal bandwith, and to do that use a _Clos topology_, which is like a switch but expanded over a several switches. This allows to have full bandwidth available for each server pair. Fat-tree is a special instance of Clos topology, where there are several Clos topologies as lower/middle layers and then they are well-connected to the roots.

Fat-tree allows to have full bisection bandwidth, which is created by the clos-topologies linked through the inter-connected root nodes.

Fat-tree scalability -

Challenges with fat-tree:

- routing algorithms (such as OSPF) will naively choose a single shortest path to use between subnets (even though there are plenty of other minimal paths). this leads to bottleneck quickly, in theory (k/2)^2^ shortest paths available but only one will be used
- complex writing to lack of high-speed ports

**Addressing in fat-tree**

Pod switches: 10.pod.switch.1 (pod and switch between [0, k-1] based on the position) \
Core switches \
Hosts

With the addressing, there can be fowarding - two-level lookup table. \
Prefix matching on pod traffic, suffix matching on inter pod matching

Each host-to-host communication has a single static path. - this introduces a problem that a single path can be overutilized, and the rest can be underutilized.

This is colled flow collision.

_Solution_ to flow collisions:

- Equal-cost multi-path - hash flows to different equal-length paths, so instead static path between end-hosts it will be static path for each flow
- Flow scheduling - havev a centralized scheduler to assign flows to paths (leveraging SDN)

## 10.3. Data center network congestion control

ususally in TCP AIMD, we do slowstart and then do timeout, again slowstart and do additive increase later

**TCP incast problem** - data center application runs on multiple servers, and they use a scatter-gather work pattern (scatter - a client sends a request to a bunch of servers for data, gather- all servers respond to the client). More broadly, a client-facing query might have to collect data to many servers.

From switch POV: \
first, the scatter will send the request to different servers \
then the workers they will send the results back to the client (each of them will have very little data - few packets) \
however, the buffer in the switch will be filled because all of them are trying to send. \
workers will try to retransmit at the same time, because a lot of packets are lost, and the same conflict happens - this is called **TCP global synchronisation problem**.

TCP incast: \
packet drops due to the capacity overrun at shared commodify switches. - this leads to TCP global sync. \
Solutions:

- use lower timeout - can lead to spurious timeouts,
- use fake timeouts
- ~someting~

what can we do to do better: \
in essence you don't wnat to overenginneer the system, and make limitted solutions.

### 10.3.1. What if we avoid packet drops?

Ethernet flow control:

- Pause frame
  - and overwhelmed ethernet receiver/NIC can send a "PAUSE" ethernet frame to the sender to stop transmission for some time
  - limitations: designed for NICs, not switches, and blocks all transmission at the ethernet-level (port-level, not flow-level) - very coarse grained
- priority-based flow control
  - enhancement over PAUSE frames, 8 virtual traffic lanes and one can be selectively stoped and the timeout is configurable
  - limitations: only 8 lanes, possible deadlock in large networks (with PAUSE frames in the lanes)

Data Center TCP: \
pass the information about switch queue buildup to senders. Sender can slow down if the queue is almost full, or speed up if it is empty.

ECN: \
packet is marked in ACK, such that there is information that there was congestion

DCTCP ECN: \
marks only ACKs that are marked by ECN

DCTCP calculations: \
F = #ACKs marked by ECN / #total ACKs

# 11. Streaming

before it was downloading the video and watching it

now it is streaming - downloading chunk by chunk

**Challenges**:

- a lot of data to process
- smt else

## 11.1. Video compression

1. send a smaller frame
2. send a delta between the frames

**Smaller frame-level compression - JPEG compression**: \
Going grom RGB (each having its own byte) - each pixel 3 bytes. So JPEG focuses not on the chrominess (colourfulness), but on the luminence (indicates brightness), because humans are more sensitive to ligth than colour. (two other channels in the jpeg are blue and red). Thus it uses less bits per pixel, and the quality is not as affected from human eye perspective. \
Compression: initially 8 bits per each part/pixel, and after you have 1 part of 8bits, and 2 parts of 2bits. thus it is x \* 3 \* 8 / x \* (8 + 2 \* 2) = 2

**Video-level compression - H.264**: \
Compare two blocks and then check the delta where the block changed. Store only the delta. However it is highly depepndant on the content. \
There are I (intracoded) frames, e.g. JPEG frames, that are self-sustained. \
P (predictive) frames - that looks back to the I and P frames for prediction \
B (bidirectional) frames - looks forward and backward to other frames. \
I frames are the biggest, P are smaller, B are smallest

**Bitrate**: measures data size per unit time. \
It affects the file size and the quality of the video. So when it is streamed, it affect the bandwidth it uses.

**Constant Bitrate**: \
Constant bitrate -> constant compression ratio -> varying quality \
In H.264, quality is worse when the motion is higher due to the larger deltas. \
This allows also to have a constant number how much data is needed to compute. However there is a lot of data loss.

**Variable bitrate**: \
This goal is to have smooth out of the quality. It makes sure that for each time unit, you ensure that you have enough data space. \
Achieving this is a bit hard and it requires two passes - to get the average bitrate and then next pass to vary the bitrate over the peaks and lows.

Video streaming with CBR - constant bandwidth, so it is suitable for video streaming, because you can guarantee minimum bandwidth to have. \
In reality it is hard to have a constant bitrate for multiple users. \
_Solution_ - have multiple constant bitrates, thus it becomes switching between bandwidths.

**Adaptive bitrate**: \
Main idea - chop the video into small segements (chunks) and encode the segments with different bitrates \
Adaptively select the bitrate for each segment in streaming for each user

## 11.2. Video streaming protocols

Ways of doing it are either built on UDP (live streaming) or TCP and on HTTP (video on-demand services).

**RTP - real-time transport protocol**: \
primarily used for audio/video transport, widely used for real-time multimedia apps such as VoIP, audio over IP, WebRTC (BigBlueButton and Zoom (it is proprietary)) \
It is built on top of UDP.

If data is lost - it's fine, but if it is out of order, it's bad. \
So the header has a sequence number (to have in-order), timestamp (play the video at exactly the time it should be played).

To have control in RTP, the receiver contantly measures transmission quality. And exchanges information between senders and receivers. \
However, this does not support varying/adaptive bitrate.

**Video streaming protocols based on HTTP**: \
Major players are: Microsoft Soft Streaming, Adobe HTTP Dynamic Streaming, Apple HTTP Live Streaming. \
Each has a proprietary format \
Bad for the industry such as CDN (Content Delivery Network) providers - like cache middleware between sender and receiver. They have to support all these different codecs.

Why HTTP? \
because it supports progressive download. (useful in web-based media delivery for video share sites). Progressive means that playback begins while download is still in progress.

Another standard - MPEG DASH (dynamic adaptive ....): \
this model is not specification of implementation, but more about model, data formats. It is ISO standard. \
DASH data model - has a media presentation description - segments of periods that can be accessed individually. Between those segments there can be adds. In the period there can be adaptation set, which have specifications (in manifest file) of segments (basically packets of tcp).

## 11.3. ABR algorithms

**Birate selection in ABR** \
you want to have the bitrate depending on the data and the bandwidth. \
The bandwidth can vary A LOT, especially in mobile environments, so to estimate the bandwidth do an average over certain time, or rolling average to smooth it out. Problem is when there are sudden drastic changes.

**Buffer-based algorithm**: \
If there is a buffer full of video content, you can relax, and there is much lower risk of rebuffering. \
Motivation - avoid bandwith estimation, since it containts implicit information about the bandwidth. \
We define a function BBA, which takes in the buffer (which output is constant (size in video seconds)), which also has buffer occupancy. So if the input rate C(t)/R(t) - bandwidth / bitrate > 1 then the buffer occupancy grows. Thus it is safe to increase R(t) to improve quality. If C(t)/R(t) < 1, buffer is draining. Thus the function B(t) = f(R(t)) has to decide what is the best bitrate for that time. \
Goal 1: no unnecessary rebuffering (as long as C(t) > Rmin for all t and we adapt f(B)-> Rmin as B->0, we will never unnecessarily rebuffer because the buffer will start to grow before it runs out) \
Goal 2: average video rate maximisation (as long as f(B) is increasing and eventually reaches Rmax, the average video rate will match the average capacity when Rmin < C(t) < Rmax for all t<0) \

BBA in practice: usually f(B) is shifted to the right such that it chooses a little bit lower bitrate rather than max, such that the function would have cushioning

**deep reimforcement learning** \
train the deep learning model, and use the trained agent to make decisions. \
It is also possible to replace video codecs with machine learning.

## 11.4. Netflix video serving

workloads: serve only static media files, which are pre-encoded for all codecs/bitrates

Video serving stack:

- Free-BSD-current
- NGINX web server HTTP
- video served via async sendfile() and encrypted using kTLS (offloaded to NICs)
- since 2020, 200Gpbs of TLS encryypted video traffic from a single server, aiming for 400+ Gbps now

Sendfile directs the kernel to send data from a fd to a TCP socket.

Data flow:
data in disks -> put it in the memory. To encrypt it, it needs to be passed by the cpu, and put it back to the memory. then send it to the NIC. Thus mempru bandwidth is a bottleneck. \
_Optimisation_ - to achieve 400Gbps bandwidth, it would need to have 50GB/s PCI bandwidth, so to do that encryption is done at the NIC.

## 11.5. Video stream analytics

usually streaming is server -> client, but now it is also client -> cloud server.

There is a very large volume of traffic, in the wide area network.

WAN has scarce, expensive and variable bandwidth. So it is very hard to measure these things.
