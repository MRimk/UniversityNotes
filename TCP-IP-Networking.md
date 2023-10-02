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
