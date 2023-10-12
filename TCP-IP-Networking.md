<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

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

#### SLAAC

## MAC

