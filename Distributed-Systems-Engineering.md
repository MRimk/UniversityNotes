<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029 MD034-->

# Distributed Systems Engineering

## Definitions

**Distributed system** - system whose components are located on different networked computers

**Decentralized system** - system without a single authority

## Examples

Centralized distributed:

- Google
- Netflix
- Facebook

Decentralized distributed:

- The internet
- BitTorrent
- Bitcoin
- Tor, I2P
- Email
- Mastadon
- Usenet (forums platform predating Internet)
- Avionics, control systems in airplains
- E-Voting

## CAP theorem

In distributed systems you can get **Consistency** (Every read receives the most recent write or an error), **Availability** (Every request receives a (non-error) response, without the guarantee that it contains the most recent write), **Partition Tolerance** (The system continues to operate despite an arbitrary number of messages being dropped (or delayed) by the network between nodes) - and you can only choose 2 of them because it's not perfect.

## Why build theses systems

Sometimes a basic requirement

Availability, reliability and safety

Lower resource usage (in specific scenarios - e.g. Windows update)

Enabler for resilient ecosystems

Nature has shown they can work incredibly well.

## Major topics and applications

Communication: messaging, chat, voice/video

Data: storing, sharing, searching and mining

Collaboration mechanism (google docs)

Social networking (mastadon)

Deliberation, e-voting, reputation (we also need to establish fairness and correctness)

Blockchains, cryptocurrencies and smart contract systems

And more (decenctralized control systems, intelligent agents, military and civilian ad-hoc networks (MANET, VANET, FANET, etc))

## Recurrent issues and themes

Identity (real, sybil) versus location

Information integrity and privacy

Behaviour accountability (moderation)

Denial-of-service attacks

Protocol efficiency, in the normal case and under load or attack

## Why we might prefer centralized systems?

- moderation
- policy control (banks)
- easier to develop, implement, maintain, deploy
- access control
- efficiency in communication, storage, computing
- management of network, trust, control, visibility
- concurrency
- up to date data
- Legal (accountability)

- Simplicity in:
  - engineering
  - management
  - security model
  - version management
- Performance / Efficiency
- Cost

## Usenet and Gossip

**Gossip idea** - family of protocols that are also called _epidemic_ protocols. Information spread over other devices.

### Usenet

**Usenet** - User's network; worldwide, distributed discussion system (like reddit before reddit)

It had hierarchical organization of topics where it went from root to other topics and into other topics like a tree (great renaming).

Context - early 1980s:

- Pre-Internet (1980)
- Mainframes, then minicomputers but VERY expensive to own, so not personal.
- Intermittent, dial-up connections - so mainly over the phone, and since it was over the voice frequencies so at best 56kbit/s (unless some people were part of ARPANET)

Early UUCP (Unix-to-Unix copy)/Usenet Map - it was quite small and could be mapped easily.

**Why think of Usenet in 2023**:

1980s computers are still relevant just they are way smaller today (Embedded systems, IoT, Sensors)

1980s networks are still relevant - Low-Power Wide-Area Networks (e.g. LoRaNET/LoRaWAN).
They have limitations - [0.3, 50] kbit/s, 256 bytes/message, per-message pricing (~2CHF/MB)

Power and batteries are the limit of today's systems so efficiency is still relevant.

And there is churn - the change of systems while some are down (e.g. change the batteries)

#### Specifications - TODO: take from slides

- Worldwide, distributed discussion system
- Hierarchical organization of topics / newsgroups
- messages are (eventually) delivered
- ......

Everything is public and virtually no encryption (since it was considered US export, computing power and RSA was not invented until 1980s)

**Message format**:

- Header
  - Sender - jerry@eagle.uucp (username at the node)
  - Path - cbosjd!mhuxj!mhuxt!eagle!jerry (this is so that you can send a response)
  - Newsgroups - news.announce (multiple can be send)
  - Subject
  - Message-ID - _some unique identifier_ (to identify whether I already got this message)
  - Timestamp - .... (to know when it was sent)
  - Organization - AT&T (sender's organization)
  - Expiration time - .... (we don't care about this message after this date)
  - _there are more optional fields_

#### Message transmission

Basic version could be _Naive Broadcast_ - send to all known nodes, and then receiver sends to all nodes except the sender.
Problem with this is exponential flooding of network with the same message, and it is too costly to operate.

Ways to fix it: recognizing the message, converting the graph into the tree (it is extremely hard to do because of churn and adaptiveness to change, but possible - e.g. ethernet)

#### Recognizing messages with IDs

One way to do it is to create _big random number_ (e.g. 256bits) - even though it is big number, there is no integrity check or someone claiming that it is their number.

Another way is to _hash_. Problem with it is which parts of the message to compute the hash on. If everything, the path could change and the hash would not be correct. Also, hash usually is computed on binary data so there needs to be a decision what to put in the skipped places and then parsing harder because it would not be text.

**Usenet approach** - \<sequence number\>@\<node\>

How to detect / trace node misbehavior?
Check the path. Misbehaving node is always represented in the path.
If I receive a message, e.g. the path is E!MT!user, and then E!MV!user, both users see that the message passed through E. Therefore, E cannot deny being involved.

#### Fixing the broadcast

if message is known - ignore
else - send message to all peers except sender.

**Limitations**:

- well-connected nodes often receice the same message many times
- what if someone fails? (memorize and retransmit)
- do we need to send the whole message everytime? E.g. broadcasting that i have a message by sending ID and then sending message on-demand
  - early Usenet (UUCP) it was not used - because broadcast was better than few day delay
  - late Usenet (NNCP) - it was not affordable

**Solution**:
Compare sets of messages.
A->B sends "ihave id1, id2, ..., "
B->A sends "sendme id3, id4"
_Problem_ - if they have long history of message exchange, then the ihave messages will be long. _Solution_ - A stores the history of messages sent to B. (but what if the B is a new node, so then there is a tradeoff how many messages to send, so then send some amount of the latest messages)

#### Message IDs - Trade offs

How long to store the message IDs?

What happens if ...

- you store them forever? - storage space, loop around and not getting new messages
- you don't store them long enough? - message could come back into circulation and loop around if some nodes are slow.

#### Life of Usenet

Why was it so successful?
It worked.
Engineering simplicity.
Decentralized - anyone can set it up.
It was seen as "democratizing" - resistant to censorship.

What killed it (around 1995)?
(didn't kill it but) the data became too heavy
Number 1 reason - spam! Because there was no censorship, spam was not stopped (first spam was "Global alert for all: Jesus is Coming Soon", and then people found a way to make money in it)
Other causes - better alternatives, slow evolution because it was decentralized.

## Beyond Usenet: Gossip efficiency

What if we wanted to further minimize traffic?

with ihave/sendme: pro - message content is only sent once per node, con - we still need P2P communication broadcast

### Improved Gossiping

From people we can learn **Rumour mongering** - checking whether a person knows the rumour or not.

Algorithm:

- when a message M is received
- pick a random neighbor, send M
- neighbor replies "new rumour?"
- if new: repeat
- else: flip_coin() (random)
  - if head: repeat
  - else: stop

(On average we will talk to only 2 neighbors because of geometric progression expected value)

Problems:
Rumour might die.
Pros: very fast and spreads to _most_ nodes

#### How to make sure messages reach every node?

Using **anti-entropy** - pull-gossiping

Algorithm:

- Periodically (when timer fires):
  - pick random neighbor
  - send "anything new?"
  - reduce entropy (ihave/sendme)

Problems:
could be a lot of traffic
propagation could be extremely slow because the rumour is new

Expected time to cover the whole network - 1 or 2 (timer) cycles.

In general: works slowly but ensure complete coverage, at O(n) per period.

#### Gossip Quality Measures

Is your protocol any good?
How can you tell?

- Traffic $\frac{total\ traffic}{number\ of\ nodes}$
- $t_{avg}, t_{95}$ average & 95th percentile time for rumour -> node
- $t_{last}$ time for rumour -> last node
- Resistance to churn
- Residue - looking at the time t, what percentage of the nodes have not seen the message.

Broadcast: good in residue, bad in traffic, and good in time of delivery.
Rumour mongering: might not reach everyone, so quite bad in that, good in average time and traffic, but residue is not always good.
Anti-entropu: good in residue, not great in traffic, bad at average time but good at reaching the last node.
So combination of anti-entropy and rumour mongering works very well.

#### How can we "delete" rumours?

Instead of propagating the data in the database, we want to delete it.

To delete it, we can spread the rumour to delete it. But the problem is that we keep the original rumour and the death certificate ("delete this") rumour.
Also, rumour can get resurrected - because it is decentralized system, so someone has to keep the death certificate alive.

#### Few applications of Gossip

Metadata propagation

Failure detection

Group membership

$\uarr$ databases uses gossip to spread metadata, but the data itself is spread normally.

E.g. Apache Cassandra, CockroachDB, Consul

#### Failure detection

Adding a heartbeat bits to each message sent by the node with a counter. Later anyone can check when was the last time it was heard from that node.

## Finding data among (many, unknown) peers

May open questions:

- where can the data be found?
- Does the data even exist?
- Who knows about it?
- How do we retrieve it?

Most importantly:

- What can we assume about the peers and the network?

### Distributed Search algorithms

Two families:

- Unstructured search:
  - Robust to churn, instantly adptive
- Structured search
  - Much more efficient many more problems

#### Building Gnutella

Context (1999-2008):
No spotify, no Netflix
No BitTorrent
People still want entertainment

Specifications:

- search any file anywhere
- Complex queries

**Standard, basic algorithm**:
What can we learn from people - **Flooding**

- Gossip searches (query)
- Direct response (query hit)

Issues:
Unpredictable delays
Connectivity - how does a node reply to me?
Efficiency - all nodes asee & process all searches

**Optimizations**
Cane we not flood everyone?
**Expanding-ring search** - have limited number of steps for flooding

- Limited flooding (TTL)
- Increasing TTL on retry

What are the trade-offs?
Higher latency
Asymptotically worse O(n logn)

Pragmatically, it works

**Optimizations**
More efficient: **BubbleStorm**

- Birthday paradox - in a room bigger size, there is a 99.999\% chance that 2 people share a birthday
- Data search & storage random "meet in the middle". Spread a file in $\sqrt{n}$ nodes. Bubbles overlap and there is a high chance that someone in my bubble has the file
- If the bubble is increased by a constant (from $\sqrt{n}$ nodes) we exponentially increase the chance of someone having the file because of the birthday paradox.

Key considerations:
Asymptotically efficient $O(\sqrt{n})$
"Mostly unstructured" - robust to churn
Tunable parameters
Extremely robust/resilient - therefore it can be applied in different systems, not only search

**Unrealistic assumption** - so far we said that the node can just reply to the source, but that's not possible.

## Ad-hoc Routing Protocols

#### P2P Example - home and EPFL networks

EPFL Network <- EPFL Firewall <- Public internet -> ISP -> home router + NAT -> IP address

If laptop at home tries to connect to the PC at EPFL it cannot because firewall
If you try to connect to your laptop at home, you cannot because it does not have an IP address (if there is no port forwarding)

Problem: even in the wired state of routing, you will not be able to connect to everyone simply.

#### P2P Example - ad-hoc networks - drones

Drones can go out of range.

Bob sent out a lot of drones and wants to communicate with all of them. Drones find each other and set up links.
However, drones move around which causes the reconfiguration of the network. (similar to this, a person moves with their device in EPFL)

#### P2P Example - analysis

- peers may not be directly accessible
- peers may join or leave the network at arbitrary times
- we need to route packes through the system

Some differences:

- Churn - going offline, joining back in
- Node mobility / network reconfiguration
- Bandwidth
- Protocols / Physical layer / etc.

### Naive routing (don't do this)

Nodes advertise a distance to other nodes.

E.g.:
B -> D = 1
A -> D = 2 (through B or C)
c -> D = 1

If D loses connectivity to B and C.
B updates to B -> D = 2 (through C)
C updates to C -> D = 3 (through B)
.... it goes on and on
This is because B and C are making decision on outdated information.

### Reaching arbitrary peers in a network : AODV

Ad-hoc On-demand Distance Vector

Key idea: Flooding search for a node (e.g. E) - when we know that a node exists.
Nodes remember where the search came from. (Remember only the first search coming through). And once the answer is there, nodes walk back the path like in Usenet.
Every node along the found path gets a temporal path to the origin of the search as well.
A->B->D->E
A<-B<-D<-E

This is valid over a short time window and the idea is not to remember for a long time.

It has the same problems as flooding.

Zigbee wireless protocol uses this.

### DSDV

Destination-Sequenced Distance Vector

Key idea:

- Store next hop for any destination (O(n))
- Version ("sequence") rounting table entries

Each node periodically broadcasts its existance:
Flood the network, with increasing sequence numebrs (we know which version of this flood we are getting).

O(n^2) traffic, superseeded by newer protocols.
**versioning** idea is still on

### Quality factors in ad-hoc routing

- amount of traffic during updates/creation
- amount of traffic at rest
- robustness to churn and movement
- speed of convergence - the routing could be temporarily broken
- guarantee of being loop-free

## Compact routing and structured search

### General approach

Build a structured _overlay network_ (like a virtual LAN)
It enables significant efficiency gains

The price paid:

- more engineering effort
- nodes will need local state (to keep the strucure AND what to do when nodes disappear)
- constant fight against churn
- loss of generality

### Distributed Hash Table

Local hash tables need:

- "good" hashing function
- Random Access memory (for constant time access)
- Not too full

Most of the time hash functions are not cryptographic (to not pay the cost of calculating hash cryptographically)

Distributed hash tables considerations:

- what do we need from the hash functions?
  - Avoid collisions, not time sensitive (because of networks time cost)
  - crypto hash functions for it to be collision resistant and well distributed (because it will be big system)
- what are we missing?
  - random access memory

#### Chord DHT

Hash into a collection of RAMs
To do that we will use circular hash ID space (e.g. SHA-256)

Each node has a pseudo-random hash ID (it enables us to put the nodes somewhere in the hash value space).
What goes into that ID? (ideas: IP, MAC, time, PubK) - this has to be unique and unchanging. Only PK cannot be faked

How to approximate the RAM:
divide space up between the nodes
Each node owns the space to its successor

API:
PUT(key,value)
GET(key) -> value/error

Problems:

- churn
- resource allocation
- security (malicious)
- routing information (as in who is ahead and behinf you in this pie)

**Reliability**:
How to prevent data loss?
Define a redundancy factor r
And copies are stored by "owner" node + (r-1) successors.

**Load**:
What is the expected load per node?

Load ~ $\frac{\text{# of nodes} \times \text{# of kv pairs}}{\text{redundancy}}$

**Performance**:
How do we make this O(log n)?
(in storage, network, etc)

Using only the successors O(1) routing table but O(n) access time

Binary search makes it O(log n) for both.
Finger tables:
Contains my successor, 1/2 circle from me, 1/4 circle from me, 1/8 circle from me...
We are using SHA-256, so we expect to have 2^256 numbers (HUGE, and most of this will be empty), that is why we expect log n spaces in the routing table.

**Churn**:

Need to handle:

- concurrent joining
  - there are challenges - e.g. a lot of nodes joining between A and B - therefore a lot of changes
- nodes leaving (gracefully)
  - replicating data, changing routing tables
- nodes leaving (unresponsive)
  - making others successors while successor is pointing to another value (**see drawing**) TODO: insert drawing
  - because of this system is going to underperform

Approach:

- split correctness and performance (tolerate some incorrectness)
- transient failures can be retried
