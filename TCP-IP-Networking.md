<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

- [TCP/IP Networking](#tcpip-networking)
  - [Layers](#layers)
    - [Application layer](#application-layer)
    - [Transport layer](#transport-layer)
    - [Network layer](#network-layer)
    - [Data link layer (MAC layer)](#data-link-layer-mac-layer)
    - [Physical layer](#physical-layer)
    - [Skipped first part of the lecture](#skipped-first-part-of-the-lecture)
  - [Network layer - middle](#network-layer---middle)
    - [IP Rule #1 = Structured addresses + Longest prefix match](#ip-rule-1--structured-addresses--longest-prefix-match)
    - [IP Rule #2 = Don't use routers inside LAN/subnet](#ip-rule-2--dont-use-routers-inside-lansubnet)
    - [IPv4](#ipv4)
      - [Special addresses](#special-addresses)
    - [IPv6](#ipv6)
    - [NAT](#nat)
      - [What does it do?](#what-does-it-do)
      - [How does NAT maintain NAT table?](#how-does-nat-maintain-nat-table)
      - [Servers behind NAT](#servers-behind-nat)
      - [NATs and IPv6, v1](#nats-and-ipv6-v1)
      - [NATs and IPv6, v2](#nats-and-ipv6-v2)
      - [Carrier-grade NATs](#carrier-grade-nats)
      - [More on NATs](#more-on-nats)
    - [MAC address resolution](#mac-address-resolution)
      - [MAC address resolution with IPv6 (NDP)](#mac-address-resolution-with-ipv6-ndp)
      - [MAC address resolution with IPv4 (ARP)](#mac-address-resolution-with-ipv4-arp)
      - [Security issues with ARP/NDP](#security-issues-with-arpndp)
      - [Secure NDP](#secure-ndp)
    - [Host/Interface Conifguration](#hostinterface-conifguration)
      - [DHCP](#dhcp)
      - [SLAAC (Stateless Address Autoconfiguration)](#slaac-stateless-address-autoconfiguration)
    - [there is other stuff in slides that i skipped - 58-74 in ip](#there-is-other-stuff-in-slides-that-i-skipped---58-74-in-ip)
  - [MAC](#mac)
    - [Medium access control](#medium-access-control)
    - [Mutual exclusion](#mutual-exclusion)
      - [ALOHA](#aloha)
      - [CSMA (carrier sense multiple access)](#csma-carrier-sense-multiple-access)
      - [CSMA/CD (Collision detection)](#csmacd-collision-detection)
      - [CSMA/CA - WiFi](#csmaca---wifi)
    - [Switched ethernet](#switched-ethernet)
      - [Forwarding frames](#forwarding-frames)
      - [Spanning Tree Protocol (STP)](#spanning-tree-protocol-stp)
    - [Ethernet frame format](#ethernet-frame-format)
      - [MAC Unicast](#mac-unicast)
      - [MAC Broadcast](#mac-broadcast)
      - [MAC Multicast](#mac-multicast)
    - [Virtual LANs](#virtual-lans)
    - [Bridges](#bridges)
    - [Security aspects](#security-aspects)
  - [TCP and UDP](#tcp-and-udp)
    - [UDP](#udp)
      - [UDP is message-oriented](#udp-is-message-oriented)
      - [Socket library](#socket-library)
      - [Socket from Operating system perspective](#socket-from-operating-system-perspective)
    - [TCP](#tcp)
      - [TCP delivery guarantee](#tcp-delivery-guarantee)
      - [Sliding window](#sliding-window)
      - [Flow control](#flow-control)
    - [TCP Connection and sockets](#tcp-connection-and-sockets)
      - [Sockets](#sockets)
      - [MSS and segmentation](#mss-and-segmentation)

# TCP/IP Networking

## Layers

Layers are abstractions of services with specific interfaces on the devices.

Layers (top to bottom):

1. Application (HTTP, FTP, email)
2. Transport (TCP, UDP)
3. Network (IP)
4. Data link (Ethernet)
5. Physical (fiber optics, wires)

We need layers to organize the systems. It offers flexibility and modularity.

Each layer is built on top of another and offers functionality to the layer on top of it.

### Application layer

Creates a commnunication connection.
Transfers files, etc. (encryption)

### Transport layer

Creates a virtual link.
Uses ports.

### Network layer

Packet switching over many links

It is more efficient than message switchin because it reduces buffer required in routers, and reduces end-to-end delay.
This is because the each device in the sequence needs to get the whole message from the link.

Basic functions:

- Forwarding - when a packet arrives at a router's input link, the router moves the packet to the appropriate output link. It is based on the packet header.
- Routing - network layer determines the route/path. They run routing protocols.

Forwarding - most common protocol IP
IP forwarding is based on the IP addresses.
It offers best-effort approach so there is no guaranteed delivery. Packets could be delayed, dropped, or reordered - the flow can take different routes/paths.

In the LAN all device IP addresses have same prefix (common part).

In IPv4 it is 32bit addresses.
In IPv6 it is 128bit addresses and uses hex notation.
They are incompatible, since IPv6 has different headers.

IP subnets - LAN
All machines have to have same prefix.
IP subnet prefix is specified using a subnet mask - if it is 16bit subnet mask, then the last 16 digits are free to choose.

### Data link layer (MAC layer)

Is responsible for moving data from one node to an adjacent node over a **single** communication link (wired or wireless)..

Services provided depend on the physical link.

Possible functions/services included:

- error detection and correction
- reliable delivery
- collistion avoidance
- flow control
- link access and multiplexing for the transmission medium

This layer uses MAC addresses (48bits) which are set by the manufacturer.

The packets are frames that are delivered to anyone that has access to the link and only the one that it is addressed to takes the frame.

Routers vs switches

Router = a system (or program) that forwards packets based on IP addresses
Switches = a system (or program) that forwards packets based on the MAC addresses
LANs are interconnected by routers and there every machine in LAN has to know IP address of the 1-hop router (default gateway)

### Physical layer

It transforms bits and bytes to the waves. Does all the encoding and decoding.

Bit rate is bits per second.
Bandwith is width of the frequency range that can be used ofr transmission over the channel.

There are limits to some channels (e.g. Shannon's law)

### Skipped first part of the lecture

## Network layer - middle

### IP Rule #1 = Structured addresses + Longest prefix match

goal of IP is to connect all systems using IP addresses

Every network interface has a structured IP address that is prefix + suffix.

Router has a forwarding table that links prefixes to output

### IP Rule #2 = Don't use routers inside LAN/subnet

Implication:

- between LANs/subnets use routers, inside each subnet do not
- hosts in same subnet must have same subnet mask and same subnet prefix

### IPv4

32 bits usually writen in dotted decimal notation.
Unequely identifies one interface in the internet (in principle)

#### Special addresses

| address                                   | meaning                                                                                      |
| ----------------------------------------- | -------------------------------------------------------------------------------------------- |
| 0.0.0.0                                   | absence of address                                                                           |
| 127.0.0/24 for example 127.0.0.1          | this host (loopback address)                                                                 |
| 10.0.0.0/8, 172.16.0.0/12, 192.168.0.0/16 | private networks (e.g. at home) used by anyone, but cannot be used on the public Internet    |
| 100.64/10                                 | private addresses used only by Internet Service Providers (ISPs)—Carrier Grade NAT addresses |
| 192.88.99/24                              | IPv6-to-IPv4 relay routers                                                                   |
| 169.254.0.0/16                            | link local address (can be used only between systems on same LAN)                            |
| 224/4                                     | multicast                                                                                    |
| 240/4                                     | reserved until recently                                                                      |
| 255.255.255.255/32                        | link local (LAN) broadcast                                                                   |

### IPv6

Why new version - IPv4 address space was too small
What does IPv6 do: same thing as IPv4, but with more address space but is not backwards compatible

Forwarding tables work essentially the same with prefixes.
Except it uses local IP address with interface number separated byt %

For every IPv6 interface there has to be a global IP address and local IP address.

Compression rules for IPv6 addresses:

- uses hex digits in hextets (4 hex digits)
- hextets separated by :
- leading zeroes in a hextet are omitted
- :: replaces any number of 0s in more than one hextet; appears at most once in address

Only one block 2000/3 is allocated for global unicast addresses.

### NAT

Internet service provider gives one IP address, but if you have n devices at home you need more than one IP address.

NAT is motivated to not run out of the IP addresses by creating local network addresses. This applies to VMs and a single host.

**Goal of NAT:** allow n > 1 devices to use one single IP address. It is a middle box that deviates from the TCP/IP arch - it violates:

- the IP principle that addresses should identify hosts uniquely
- layering

#### What does it do?

It translates internal IP addresses and port numbers to NAT IP address and NAT port numbers.
From outside, one sees only NAT IP address (public) and NAT port

NAT forwarding is based on **exact matching** in NAT table. Implemented by iptables in Linux; ports are UDP or TCP.

NAT because of this reduces the amount of processes possible to run on a machine, but we have 65000 available port numbers. And adds additional delay because the packets are processed - transport and network layer headers edited.

There could be nested NATs.

Internal addresses in IPv4 are typically private addresses.

#### How does NAT maintain NAT table?

It creates entry on-the-fly when cliend on internal network contacts server on external network.
NAT chooses a NAT port that does not create collision in the table.

#### Servers behind NAT

Assume A has a server on tcp port 5000.

Problem: Automatic operation automatic operation of NAT requires for the server to start the communication which does not happen.

Solution: manual configuaration of port forwarding in NAT.
A still needs to find out its NAT address to advertise to other devices. A discovers its NAT IP address with STUN server or UPnP (it is unsafe and we shouldn't use it).

This provides protection to home network: a server port number can only be accessed if explicitly configured, while servers on the internet are exposed in general to attacks and need to be actively protected.

NAT table port entries are allocated randomly (pseudo randomly), and the entries are not there forever.

#### NATs and IPv6, v1

NAT was developed for IPv4, motivated by the lack of IPv4

With IPv6, home routers often do not use NAT because provider typically allocates a block of IPv6 addresses, not just one as with IPv4

With IPv6 the home router provides protection by acting as a filtering router - allows communication from outside only if initiated from inside.

#### NATs and IPv6, v2

There is a system to still use IPv6

Assume local network receives only one IPv6 address, not entire prefix.
Solution: use NAT with link local IPv6 addresses on internal network.
Local network should be restricted to one LAN (only one subnet)

this is used by the VirtualBox("NAT network")

#### Carrier-grade NATs

"Carrier-grade" NAT shares p external NAT addresses with n > p internal hosts. So there are multiple external interfaces.

Example is VPN access of EPFL. Some users might be connected with the same address, or some might be different.

These are NATs behind NATs: A is 192.168.178.34 at home, as 10.252.13.211 in EPFL VPN and as 128.178.15.x in the public internet

Some internet service providers do the same in order to reduce the number of IPv4 addresses allocated to end-users. They use the block 100.64/10 instead of 10/8

#### More on NATs

Mapping (internal addr, internal port) -> (NAT addr, NAT port) is independent of the external corrsepondent. If this mapping is constant, then **full cone NAT** can be used to support servers behind NAT. (servers use STUN servers to get their publicly seen IP address)

Not all NATs are full cone.

There is a **symmetric** NAT that has the mapping (internal addr and port, external (someone outside) addr and port) -> (NAT addr, NAT port). So the mapping learnt by one external correstpondent S cannot be used or guessed by another S'

ICMP packets don't have a port number. Some NATs don't support ICMP, but many do. Those are smart NATs that manipulate _ICMP echo request identifier_ instead of the port number.

### MAC address resolution

WHY?
And IP machine A has a packet to send to a next-hop B (could be a final destination or next-hop router). A knows B's IP address, and A must find B's MAC address.

HOW?
Broadcast or multicast a packet to LAN asking "who has the IP of B?"
All hosts that have IP address of B respond with their MAC address.

#### MAC address resolution with IPv6 (NDP)

1. A sends a Neighbour Solicitation (NS) packet using the Neighbour Discovery Protocol (NDP) with question "who has IP address B"
   1. The dest IP address of the NS packet is a special multicast address (solicited Node Multicast Address) = last 24 bits are copied by IP's address
2. B responds with Neighbour Advertisement (NA) packet, giving its MAC address. This NA packet is sent by B to A
3. A reads NA, stores MAC address in neighbour cache (also called ARP table). This entry expires after a timer declared by OS.

NA, NS packets are carried as ICMPv6 packets - next-header = 58 (0x3a), inside IPv6 packets.

The convention in IPv6 is not to use broadcast.

The solicited node multicast address:
last 24bits are left for the identifier (reuses the last 24 bits of the IP address), and we reser 104 bits for the multicast. This is because these nodes are in the same LAN

The more specific the question is the better for the network.

#### MAC address resolution with IPv4 (ARP)

ARP request/ARP reply instead of NS/NA packets

Theses are MAC frames where Ethernet = ARP (86dd)

ARP request is broadcast to all nodes in LAN

ARP is another protocol that is in-between MAC and Network layers. In its header there is a Protocol field that shows which protocol initiated the request, and in this case it would be IP.

#### Security issues with ARP/NDP

ARP requests/replies may be falsified (ARP spoofing)
Atacker will capture all packets intended to B. This is the way to do MITM attack in LAN.

Prevention: This is done only in big enterprise networks.
using smart switches - they remember association the IP to MAC addresses. This is called **DHCP snooping**, where DHCP is used to automatically configure the IP address at system startup.

**Dynamic ARP inspeciton** - switch filters all ARP (or NDP) traffic and allows only valid answers - removes broadcasts (IPv4) and multicasts (IPv6)

#### Secure NDP

Make NDP spoofing impossible

How?
Assymetric crypto:

- Host B has a pub/priv key par P/p
- B uses CGA( cryptographically generated address) = secure hash of P and IPv6 address prefix (and other fields such as counters) - this binds the IP adddress to P
- NA message sent in response to A contains a signature computed with p
- A can verify signature using P
- only the owner of p (secret) can send a valid NA

Some necessary things: they need to have strong has function and Resource Public Key Infrastructure (RPKI) (similar to CA).

### Host/Interface Conifguration

IP can be configured manually or automatically:

- IP address of interface
- Mask of this interface
- IP address of default router
- IP address of DNS server

Some protocols: DHCP for IPv4 and IPv6, SLAAC for stateless IPv6

#### DHCP

Server in LAN, where all the information info is kept.

Problem: host cannot contact the DHCP server since it does not know of **any** IP address initially.
Solution: broadcast in IPv4 or multicast in IPv6 in LAN to discover DHCP server
Details:

- either there is DHCP in LAN
- there isn't a DHCP in LAN and router relays the message to external server
- DHCP uses two phase commit with acks to avoid inconsistent reservations
- DHCP server suses limited lifetime allocations - DHCP lease.

#### SLAAC (Stateless Address Autoconfiguration)

It is a protocol designed to avoid configuring DHCP serverse and/pr obtain a configuration automatically even if there is no DHCP server.

How it works:

1. how auto-configures a link local address with a 64-bit prefix (fe80::/64) + a 64-bit host address part obtained by one of the following: (manually configured, derived from MAC address, randomly assigned and teporary, randomly assigned but same in same subnet, cryptographically generated address (CGA) - hash of pub key or host + subnet)
2. host performs address duplication test by sending a mylticast packet to the solicited node multicast addess with the same 24 last bits as its own address
3. host tries to also obtain globally valid address by obtaining network prefix from routers if any presend.

It does not provide DNS information.

### there is other stuff in slides that i skipped - 58-74 in ip

## MAC

### Medium access control

exists so that sharing a cable is possible and using a shared wireless radio link

If there is a shared medium, there are collisions.

Solutions:
Mutual exclusion protocol + distributed
Joint decoding -- used in cellular networks

### Mutual exclusion

Deterministic - static partitioning on time or frequency to avoid collisions (TDMA, FDMA) and works for only few users

other deterministic - every host takes a turn and passes a token to next host

Random access protocols that allow collisions but detect if they occur (retrasnmissions at _random_ time)

#### ALOHA

Collisions occur when two packet transmissions overlap and if a packet is lost - then the source has to retransmit (no retransmission strategy is defined here)

There is no feedback to the source in case of collision

Max utilization is only 18% which is small. This is assuming ideal retransmission policy

#### CSMA (carrier sense multiple access)

assumes single transitive channel (everyone can hear everyone).

improves efficiency from ALOHA by listening to the channel before transmitting

It avoids many collisions but not all because of propagation delays - if two stations sense the free medium, and then have to backoff, it can again start transmittting.

CSMA works well only if the transmission time is much larger than propagation, namely bandwidth-delay product << frame size

In order to avoid repeated collisions there is a random backoff.

#### CSMA/CD (Collision detection)

When the collision is found (transmitting and started receiving), jam signal is transmitted. Then a random backoff

Acks are not necessary because absence of collision means that the fram could be retransmitted

Random backoff increases exponentially if repeated collisions occur

Minimum frame size is necessary to guarantee collision detection -> CSMA/CD uses min frame siOld-style Ethernet was shared medium (either used
coax cables or hubs with twisted-pair coppze 64B

#### CSMA/CA - WiFi

Acks are used to detect collisions (by abscence)

Carrier sensing is used but collision detection does not always work (exposed terminal problem)

### Switched ethernet

It is based on switches = beidges

Switches forward frames based on MAC addresses and they have queuing system (frame buffers)

Switches use full-duplex cables which means frames flow simultaneously in both directions without having collisions.

Ethernet is transparent protocol and since there are no collisions, CSMA/CD is desabled by default

#### Forwarding frames

Exact match forarding algorithm:

- listen to all traffic on all ports
- for each frame - read the destination MAC and obtain the destination porrt (if dest port == origin port, no need to forward)
- if dest address is not in the table - broadcast to all ports except origin

Smarter switches handle multicast addresses separately

Populating:

- self-learning from source MAC address
- learnt addresses time out if not re-learnt after "ageing time"

different from IP routers that use routing algorithms

This populating does not always work - if there are loops in the topology

#### Spanning Tree Protocol (STP)

Forces the active topology to be a tree that spans all switches by deactivating some links

Adapts to link failures and additions whenever needed

How?:

1. Switches elect one root switch - switch with smallest label ID
2. Only links that are along the shortest path to root switch become active - spanning tree = set of shortest paths to root switch
3. all switches monitor whether the root is reachable, and if not re-computation of a new spanning tree

It is distributed algorithm
Each link between switches has a (configurable) cost
Shortest paths are identified by using a variant of the Bellman-Ford algorithm

**Side-effect** - all frames go through the spanning tree, direct link between two non-root switches may not be used even if it is optimal

It is less efficient than the shortest path
Some more sophisticated switches implement Shortest path bridging instead of STP

### Ethernet frame format

Has error detectio with Frame Check Sequence. Uses CRC 32bits
If frame fails the check, it is dropped.

#### MAC Unicast

MAC address - 48 bits - unique worldwide (adpter ID)

In shared-medium LAN - all stations read all frames but keep only if destination address matches
In switched Ethernet - switches forward only to ports that need it

#### MAC Broadcast

In shared-medium LAN all machines receive the packet and don't discard it
In switched ethernet - broadcast frames are sent on all nodes and ports on the spanning tree

#### MAC Multicast

MAC addresses with 8th bit == 1 are multicast addresses

makes sense only in switched Ethernet - ethernet adapter discards multicast packets unless host subscribes to address
non-smart switches broadcast such frames
smar switches send only to relevant nodes

### Virtual LANs

Invented to have more traffic isolation
to make more efficient use of switches
to manage users

Goal: decouple who belongs to which LAN from their physical location

They are handled as if they are physically separate

How does it work?:

- configure which switch port belongs to which VLAN
- switch handles ports of different VLANs as separate, non communicating worlds
- switches are interconnected via **trunk** ports that use VLAN tags in an ehternet's extended header in order to correctly allocate frames to VLANs

### Bridges

switches that are used between different medium access technologies (e.g. WiFi and ethernet)

**Wifi access point** is a bridge example.
It consists of wifi base station and a switch with an ehernet backend (called the Distribution System)

### Security aspects

MAC addresses are sent in the clear, so there are possible attacks:

- eavesdropping
- free riding
- impersonation

Solutions (MACSEC):

- Access control - requires user to show credentials before allowing access to the network
  - share secret (E.g. Wifi WPA-Personal) - same password for all users
  - per-user authentication (e.g. wifi WPA-Enterprise) - user has a personal password
- Authentication - every MAC frame is signed using crypto and numbered - prevents free riding and impersonation
- Encryption - MAC frame payload is encrypted (not MAC address) - prevents eavesdropping

## TCP and UDP

Transport layer makes the network services available to programs and is in end-systems only

### UDP

uses port numbers and the server's port numbers must be well-known to clients

src and dest port numbers are inside transport-layer header

**Server** - the role of a program that waits for requests to come (abstraction in this context)

#### UDP is message-oriented

UDP delivers the exact message or nothing

one message, up to 65535 bytes

consecutive messages may arrive out of order
messages may be lost

If a UDP message is larger than the maximum size for the IP layer (MTU) then fragmentation is done -this is not visible to the application layer

#### Socket library

there are IPv4 and IPv6 sockets, so to get what we _can_ have we do `socket.getaddrinfo()`

This does not affect UDPv6 - UDP and TCP are not affected by IP layer

IPv6 socket can be dual-stack - (on some dual-stack machine) IPv6 socket can be bound to both IPv6 and IPv4 addresses of the local host
This is achieved by mapping correspondents' IPv4 to IPv6 addresses using the IPv4-mapped IPv6 address format - last 32 bits are of IPv4

#### Socket from Operating system perspective

Socket is just 2 buffers - one for sending and one for receiving.
Sending buffer is necessary because if there is a backoff, the information needs to be stored somewhere
Receive buffer is necessary because we could be receiving more data than the application can read. But there could be a buffer overflow - UDP does not do anything about this.

At sending side OS sends the UDP datagram ASAP

At receiving side OS reassembles UDP packets (if needed) and keeps them in buffer.

### TCP

Packets could be lost because of buffer overflow, physical layer errors, or reordered because of different paths

UDP does nothing about that
TCP does that at transport layer

TCP guarantees that the data is delivered in order and without loss

TCP does not do data fragmentation, it makes packets of the required MTU size

#### TCP delivery guarantee

Sender sends packet with seq a:b, receiver sends back ack with b. Ack is a cumulative ack which means that it has received everything up to that ack.
There are also selective acks (sack) - that received a packet of x:y, such that retransmission would not include that one.

TCP receiver uses a **receive buffer** = _re-sequencing buffer_ to store incoming packets before delivering them to application
This is because:
Application might not be able to take in the data
pakcets might have arrived out-of-order but kept invisible to application

#### Sliding window

the receive buffer may overflow if one piece of data "hangs" (myltiple losses affect the same packet, so there are multiple out-of-order packets fill the buffer)
The sliding window limits the number of data "on the fly" - not yet acknowledged

How does it work:
window size - 4000B, each segment - 1000B
Only seq numbers that are in the window may be sent
lower window edge = smallest non acknowledge sequence number
upper window edge = lower edge + window size

Fixed size window cannot prevent receive-buffer overflow, because the receiver application might not be fast enough to read the data.

#### Flow control

Adaptive window size is sent from the receiver to the sender to show how much space is currently in the receive buffer.
Sender adapts source's sending rate to the receiver's buffer.

it's not equal to congestion control.

_What is a problem when a 0 window is sent:_
We need to make sure that the sender is later unblocked. This can be done by sending the same ack but with different window. But this new ack can be lost.
So TCP allows sender to send 1 byte to check whether the windown has changed (like probing)

What is the minnimum window size required for sending at the maximum possible rate: RTT \* link capacity (bits/second)

### TCP Connection and sockets

I know SYN sequence and FIN sequence

#### Sockets

Difference from UDP - they need to open and close the connection

TCP connection is identified by src IP, src port, dest IP, dest port

From OS POV the buffers are re-sequencing buffers.

#### MSS and segmentation

TCP avoids to segments its data at IP layer so makes segments into maximum segment size (MSS).

Default values are:

- 536 bytes for IPv4 operation
- 1220 bytes for IPv6 operation

Otherwise negotionated in Options header field during connection setup

TCP offers streaming service, which is not great for connections that do not immediately fill up the TCP block (HTTP/2, streaming video, etc)
