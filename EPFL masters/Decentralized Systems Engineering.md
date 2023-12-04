---
title: Decentralized Systems Engineering
---

<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029 MD034-->

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
  - making others successors while successor is pointing to another value (**drawing of successors pointing to next, next next, etc**)
  - because of this system is going to underperform

Approach:

- split correctness and performance (tolerate some incorrectness)
- transient failures can be retried

## Decentralized Storage & Distribution

### Storing data (reliably)

On local machine:
Storing in redundancy (RAID - redundant array of independent discs, FEC/ECC/erasure codes) - encode the data and some additional data such that we don't lose it.

Distributed:
Block-, filesystem- or object-level access (SAN, NAS, AWS S3) - different levels of abstraction
Redundancy - should all 1000 computers have a copy - no, but more than one copy
Concurrency control - locking does not scale well but is easy
Sharding - keeping a subset of the data in one place

### CAP theorem - reminder

Definitions:

- Consistency - anyone reading will read the last write (or error)
- Availability - all requests get a non-error reply
- Partition tolerance - dropped/delayed packets

All of them overlap, but not all 3 of them.

Beyond CAP:
think of availability as latency -> Latency vs consistency (how much am i willing to wait to be consistent or how consistent do i need to be if i want to wait little time)
-> eventual consistency (at some point i will be consistent)

### Goals and Challenges

Availability - robust to churn, individual node failures, etc (durability could also be included but also independent - how robust are we to losing data)

Consistency - how do we stay in sync? weak or strong consistent?

Scalability, load balancing - efficiency in bandwidth and storage space

Modifiability/mutability - if i want to have data that is modifiable, how do we manage consistency; how to manage multi-writing.

Malicious security - eclipse (have enough keys to take away the data), tampering and rollback attacks (serving old version of the data)

InfoSec (CIA triad) - confidentiality, integrity, availability - access control, logging, accountability

(Logical) data organization - "flat"? files? directories? databases? graph?

(Physical) data location - where should it be stored?

### Building BitTorrent

#### Specificaiton

Distribute a large, static (immutable) files:

- from a source node with limited bandwidth
- to a large number of users
- as fast as possible

Scalable - 22% up- and 3% downstream of global internet traffic

Assume users are self-interested = don't assume they want to help

How to build this? Core intuition? - turn downloaders into uploaders

#### Distribution

Source has 6 chunks of data. At any point it is uploading at most to 2 nodes.
Distribute chunks to the nodes in different steps, and when all the chunks are in the network, all nodes eventually get the full data.

#### Sub-problems

- Advertising a file
- how to find peers to download from
- verfiying integrity of large files (or parts of them) - not a virus
- optimizing performance
- aligning incentives (downloaders vs uploaders)

##### Distribution and integrity of (large) files

A client should be able to verify:
parts of file, as they are downloaded
the whole file (after download)

Solution:
part 1 - compute hashes for parts (chunking)
part 2 - hash tree (merkle tree) - hash over the hashes building a tree (otherwise ineficient to transfer data ie all hashes)

##### Finding peers / bootstrapping

Two options:

- Trackers - server whose role is to send peers to other peers who have the files
- Mainline DHT (based on Kademlia) - key is the hash of the file, value is the list of peers who are working on that file.

Join the swarm and connect to ~80 peers.

##### Publishing new content

1. "Prepare" the file (chunks and build Merkle tree)
2. Register with a "tracker"
3. Publish a .torrent file or magnet (DHT) link

##### Performance and Incentives

One of the key ideas is to download rarest data blocks ("chunks") first - entropy maximization

Use Tit-For-Tat strategy ("choking" protocol) - if you're mean to me I am mean to you, if you're good to me I am good to you.

- "chokes" punishes peers that are not uploading
- "unchokes" peers with the highest upload rates
- "optimistic unchoking" looks for better/bootstrapping peers

Make the download rate proportional to the upload rate for each peer.

BitTorrent does not take into account where (location-wise) your peers are. And the download and upload speed are not symmetrical.

#### BitTorrent-inspired solutions

Servers:

- Twitter's "Murder" server deployment system (went from 40min to 12s deployment)
- Facebook's same thing

Games:

- "Blizzard Downloader" - WoW, Diablo 3
- Wargaming's - World of Tanks, ...

OS:

- Windows Update
- others have tried - "DebTorrent"

#### BitTorrent limits

Why did DebTorrent fail to materialize?

- Not suited for small files (overhead)
- Not suited for sharing overlapping sets of data (across torrents)
- Data is immutable (and not re-usable across torrents)
- Locality of peers is ignored - ISPs do traffic-shaping

For DebTorrent, both "1 huge torrent" or "1M+ small ones" = inneficient

### IPFS - Inter-Planetary File System

Protocol for P2P distributed file system, fully decentralized

Designed to address (perceived) flaws in HTTP - why do i need to visit this exact website, link-rot, my data etc

Deployed at massive scale:
2023: >300k nodes, millions of unique weekly users, 100+ PiB stored

A decentralized file system inspired by:

- Kademlia DHT
- BitTorrent (block exchange)
- Git versioning
- Self-certifying filesystems

#### Representing a filesystem in a DHT

Everything is immutable

All objects are self-certifying (files, links, folders, changes) - prevents websites being exact copies of each other; the hash of data coming from different nodes will be the same even if it's coming from different places.
ID is computed based on object's hash

Any IPFS object (file, folder) is represented in the same way:

```go
type IPFSObject struct {
  //array of links
  links []IPFSLink

  //opaque content data
  data []byte
}

type IPFSLink struct {
  Name string       // target's name
  Hash Multihash    //... hash
  Size int          // ... size
}
```

##### Representig a file < 256kB

It is a blob, and representation looks like git

##### Representing a file > 256kB

Split it in chunks - list of smaller files

##### Representing a directory

Object that has links to files, to subdirectories. This is a directed acyclic graph.

##### Versioning

- Git-like
- Build a mMrkle DAG
- Build a snapshot of the current state
- Hash of both content and its parent commit's hash
- Creates a Git-like log of versions

Problems:
How do we know the latest version?
merge problems

##### Naming (mutable) data

Objects are immutable so:

- use a separate namespace for mutable data
- use mutable, signed pointers to immutable data
- not content-addressable - advertise link on routing system (because the system is dynamic, we need to announce it every ~4 hours)
- built-in limit to rollback attack (since the link has an expiration time)

These are independent of the file system.

For naming we will use an extension that is IP Naming System:
use public key to make sure that no one else is using it

### Shifting paradigm - Local-First Software

Git, Google Docs, Apple Notes - work offline and you (nearly) get the full experience

How?
Multi-versioning concurrency control - how to "merge" versions that forked?

Goals:

- local client is first-class citizen
- works offline
- eventual consistency
- ideally - can handle forks

What tool - Conflic-Free Replicate Data Types (Data structure + Algorithm + Protocol)

### Conflict-Free Replicate Data Types (CRDTs)

Various types:

- Values (simples approach - last write wins)
- Counters (allow machines to count)
- Lists
- Text

Categories:
Operation-based - commutative replicated data types (CmRDTs)
State-based - convergent replicative data types (CvRDTs)

#### G-Counter CRDT

Grow-only counter - replicated across N machines

Add(x) - updates our local counter

Query() - returns the value

Merge(other_state) - merge's other's state

```python
class GCounter(object):
  def _init_(self, i, n):
    self.i = i # server id
    self.n = n # number of servers
    self.xs = [0] * n

  def add (self, x):
    assert x >= 0
    self.xs[self.i] += x

  def query(self):
    return sum(self.xs)

  def merge(self, other):
    zipped = zip(self.xs, other.xs)
    self.xs = [max(x, y) for (x, y) in zipped]
```

#### Local-First Software - simpler backends

Application becomes sequence of messages storage and sync, and therefore it becomes way easier to deploy.

## Replication of Consensus

### Replication

Replicating storage or nodes in a distributed system

#### Storage Replication

Storage-specific replication techniques assume that node stays alive, and there is a focus on making sure that disk failures are supported.

Classic storage replication techniques:
e.g. disk failure -> RAID (redundant array of inexpensive disks)

- RAID1 - mirroring (2 copies on 2 disks)
- RAID5 - striping with parity. (2 disks store one stripe each and third one stores parity disk). Tolerates any **single** disk failure
- RAID6 - double parity. Tolerates 2 disk failures.

Disks are passive and there is an "authority" who knows/governs the "state of universe"

Replication of distributed _Nodes_ - we want to replicate any node such that when one fails, the system can work. **Problem** - there is no "authority"

### Agreement or Consensus

There are several (n) nodes agreeing on one state (value).

One way to categorize consensus protocols broadly: permissioned or permissionless (since 2008)

- Permissioned - algorithm assumes a well-defined, closed group of n nodes.
- Permissionless (Bitcoin) - makes nodes prove that they did something - proof-of-work

Narrower categorization for permissioned protocols: Crash failures (loses power, becomes unoperational) vs Byzantine failures (a node might be malicious or compromised)

Many different consistency models - **How** consistent?

- Serialization - we want all nodes agreeing on a single history
- Eventual consistency - nodes may disagree for a while but eventually come to agreement

#### Paxos consensus algorithm

Assume that there is a set of state nodes - Acceptors. For now have 2 of them. (s1, s2)
And there are clients which drive the agreement - Proposers (alice, bob)

_Case 1:_
Assume Bob does not exist, Alice proposes state transaction T, and the state nodes will say yes to T because they have not heard from Bob.

1. **Problem** - alice might not know of a failure before it is accepted, s2 might fail before sending back yes.
2. If alice wants to tolerate f failures (f < n), then it must be able to move on after waiting for at most n-f answers.

_Case 2:_
Now assume Alice and Bob proposes transactions T1 and T2, and now the **problem** is that if both wait for just one server to answer, they might disagree (s1 yes to Alice, s2 yes to Bob)

This illustrates **main principle**: To reach agreement of only 1 value, we need to have a _majority_ - n > 2f (or n >= 2f + 1).

Now have 3 acceptors, and 2 clients - alice and bob.
A and B propose T1, T2.
Alice transaction gets accepted by s1 and s2 first, bob's gets accepted by s3, and s2 replies to bob that alice won. --> Server 2 is the only disambiguating authority, and if it fails, no one knows who won.

Also a problem
If there are more proposers.
Now have 3 acceptors, and 3 clients - alice, bob, and charlie.
A, B, and C propose T1, T2 and T3.
s1 accepts A, s2 accepts B, and s3 accepts C -> **Fundamental problem** - no one gets a majority.

**Fundamental problem** - how do you know when consensus has been reached?
each client has $\le$ n-f observations, so it doesn't have full picture.
e.g. If i talked with majority and got 0 yes answers, I know i failed; If i talked with majority and got 1 yes answer, i might have succeeded.
e.g. if I got f yeses, then i might have failed.
=> "I don't know"

if i got 0 yes, definitely failed; if i got f+1 yes, "looks like" i succeeded.

##### Fundamental challenges

1. Be able to _try again_ on failure.
2. If agreement might have happened, the future tries have to be consistent with past attempts that _might_ have agreed

**Tackling try-again**:
Use lock-step time - steps or "ballot numbers" (they are logical steps not real time steps)

Alice convinces s1 on step 1, B on s2, C on s3, so now try again. They start again all, but alice gets first to step 2. So alice wins.

**Tackling phases**:

1. figure out if I _can_ succeed
2. figure out if I _did_ succeed

Paxos has a time-step reservation system:

1. client asks each server to _reserve_ ("prepare") step for me
2. only if succeeds, client asks each server to _record_ proposal.

E.g. 3 servers, 1 client Alice.
Alice sends a proposal "reserve step 1" to each server, waits for answers. Gets majority of the answers "yes", so majority moves forward to ask "record 1:T". And since nobody broke alice's reservation, those recordings are successful from the majority, so the servers knows that alice had a majority.

What happens when s3 dies (and s1 got another reservation from B, which means s2 and s3 guaranteed recording of alice -> s2 is the only one left confirming this)?
S1 know that alice _might_ have succeded, s2 knows that alice succeeded.
Bob while reserving step 2 on s2 sees that alice might have succeeded in step 1, and if it succeeds in step 2, it records latest/highest prepared T (because bob is obligated to be consistent with alice's attempt).

**Key rule of Paxos** - if it's possible that at previous timestep client might have succeeded, current client at current step must carry out that previous attempt.

e.g. 3 servers, 2 clients Alice and bob:
Alice sends a proposal "reserve step 1" to each server, waits for answers. Gets 1 answer "yes" from s1, Bob sees that one server might have succeeded, and sends his reservation for step 2. Bob succeeds at s2 and s3, Bob sends record T', and then s3 records T'. And this depends on the majority that agrees to have the view of overwriting or saving alice's step.

## Cryptography

Cryptography is not reliable unless implemented properly, and unless used properly. And it is not a solution to all problems

- Shared-algorithm cryptography
- Symmetric-key cryptography
- public-key cryptography (encrypt with pubkey, decrypt with privkey; sign with privkey, verify with pubkey)
  - interactive key exchange (Diffie-Hellman key exchange)
  - Elliptic curve key exchange (ECC)
- Cryptographic hash functions
- Key infrastructure
- Threshold secret sharing

#### Elliptic curve cryptography

is based on the algebraic structure of elliptic surves over finite fileds.

Hardness (trapdoor) - hard to determine n form Q = nP, given known Q and P, and a sufficiently large n. And computing Q is easy.

Smaller keys for equivalent security than traditional crypto (e.g. 256-bit for ECC is comparable to 2048-bit RSA) -> faster operations, and smaller pubkeys -> smaller crypto

It is used in Bitcoin to authenticate transactions and every Bitcoin address is a cryptographic hash of ECDSA pub key.
Apple uses it for their services

**Requirement** - Randomness for the ECC.
Problem if it is not being used - security of private key could be compromised.
In 2010 Sony used it but used a constant instead of randomness to sign software for PS3 and privkey was recovered
In 2013 Android Bitcoin Wallet due to k being predictable

#### Key distrivution

for both symmetric and asymmetric crypto key distribution is necessary

Exchange of secret keys requires confidentiality
Exchange of public keys requires integrity

Authorities trusted to provide secret/trusworthy keys (KDC./A)

There is a hierarchy of trust - one of KDC/CA is not enough.
Problem - this is centralized, therefore attacker could carry out MITM attacks.

##### Web Of Trust (WOT)

Creating the graph where I can trust someone who is trusted by someone I already trust.
This works very well until there is a node who trusts a lot of malicious nodes.

#### Threshold secret sharing

Sharing a secrete without revealing it

Any encrypted data is secured with a private key.

- a private key is just information (a number)
- if the key leaks, anyone can decrypt the data (regardless where it is stored)

Privacy & accountabilitiy with secret-sharing, essential idea:

- split the secret key among n parties
- require only a _threshold_ t of n parties to use it.

Distributed key generation (DKG) - allows the group of nodes to create their set of of public-private keys

### drand: publc, verifiable randomness explained

#### Secret randomness

We always use secret randomness to generate cryptographic material (used in AES always)

#### Public randomness

E.g. Lottery
It is simply a random value that is meant to be public.

Its goal is often to increase the trust.

#### Verifiable randomness

public randomness is cool, but we usually wnat it to allow for public verifiability.

This requires many complex verfiable generating functions.

## Anonymous Communication

### Who has eyes to your internet usage?

- ISP
- Local network (employer's security solution)
- Governments
- Parental control
- Ads - Google, Meta, etc.
- Platforms - Amazon, Alphabet, Tencent, Alibaba,...
- VPN servers, proxies
- Spyware
- Browsers - Google, Mirosoft, Mozilla, Apple
- DNS servers

(some snooping is not that bad - deprecation of certain features)

**Hasn't TLS/encryption solved the problem?**

Metadata says everything about somebody's life.

How to determine the person on the metadata:
Patterns of behaviour (this person's IP changes regularly), network traffic of bluetooth could reveal the medical condition and a specific brand device.

**Why desire anonymity online?**

- Privacy (individuals), Security (business, governments)
- Freedom of speech / journalism / activists (escaping censorship, avoid speech being linked to oneself)
- Avoid ad targeting, tracking
- Bypass geo-blocking
- Helps criminals stay out of jail
- Helps cops investigate online crimes

### Threat model

Is out desire to remain anonymous a secret on its own?

Who are we keepking our identity from?
a website, advertisers, a platform (meta, google), a well-funded governments

What are their capabilities?
Cookies, "Supercookies", fingerprinting
Semi-honest nodes ("honest but curious")
Malicious nodes
NSA - Xkeyscore, Quantum & FoxAcid (MITM, MOTS - Man On The Side attack)
CAC (Cyber Administration of China) - Censorship, MOTS, control over platforms

**How?**
Client sends a packet to server, server responds, NSA takes the response packet from internet backbone, tells the router to drop the packet, and meanwhile sends the packet through Quantum system - TAO FOXACID which sends that packet to the client.

### The goal

- Server and receiver cannot be "linked" by a 3rd party
- Server and receiver both remain anonymous, including to each other (within an _anonymity_ set)
- Metadata must be unusable for traffic analysis
  - padding hides the size of the data (how many files could be in the size range)
  - only few people can talk with me
- Ideally - censorship-resistant

### How to achieve anonymity

#### 1-hop approach

1-hop approach - Proxy / Commercial VPN - ISP can see that you are communicating with the VPN, but they don't know what is the end communication

Advantages:

- shields user from website IP-based tracking
- prevents geolocation

Problems:

- VPN knows incoming <-> outgoing mapping
- Vulnerable to traffic analysis
- Vulnerable to hacking / coercion
- DNS might be leaking information (as a side channel because it is not forced to be under VPN)
- Vulnerable to censorship

#### 2-hop approach

2-hop approach - Apple Private Relay

There are 2 relays: you are talking to Apple, and they talk with 3rd party, which talks to Web.

Advantages:

- Shields user from website IP-based tracking
- In theory, no single party sees both sender and receiver

Problems:

- Restricted to countries allowing it
- Apple + 3rd party jurisdiction
- Limited to user's geography - business of streaming media contracts

#### Mix networks (e.g. Mixminion)

Goal - anonymize e-mail / Usenet-like traffic

Key intuition - get traffic, shuffle it and send it next step.
Each node waits for certain time, mix the packets (order, identity of the voter from the encrypted ballot), and send it to the next node.
Client splits message M in **uniform** chunks, **padded** as needed, and **encrypts** each chunk C for a path through the mix-net

Randomness is in the message destinations, which is used to prevent repeat attacks or precomputed paths.

Works with just 1 honest mixwrs

Advantage
provable (storng) anonymity
may resist traffic analysis

Problem:
Very slow, high-latency (hours)
Few users -> small anonymity set

#### Tor (The Onion Router)

Can we make mix-net work at interactive speeds?
-> tradeoff with robustness to traffic analysis

Each packet is 514 bytes

How do we find Tor relays?
There is a Guard node - which is public, and middle nodes are secret.
There are Harcoded (10) directory servers

New list of all known relays every hour - _how to agree on the list?_ -> **consensus**

Advantages:

- larger anonymity set
- low-latency
- usability, intercactive web
- highly effective against weak adversaries

Problems:

- weak to traffic analysis attacks
- web services may block tor
- adversary may become global passive adversaries

##### How can this system be attacked?

Quantum system can intercept traffic in between client and guard node.

Become a relay (lots of them) - if you can control the relays (esp. entry and exit nodes) you can do traffic analysis.
Defence - reputation of the relay

There are services inside the network which makes it harder to attack.

#### Garlic routing

Packaging together messages at router and disassemble at next one. So it has mix-net properties

#### Dining Cryptographers (DC-net)

Different - not relay-based, information coding

Based on the secure multi-party computation.

Idea: cryptographers are having dinner and a waiter tells them the bill has been paid. They want to find out if one of them paid OR if someone else (the NSA) did **without revealing who paid**

Key element - secret that is shared between pairs of cryptographers. (coin flip)
My value = Left $\xor$ Right $\xor$ (I paid)
To check whether we paid - xor all of them and if it is 1, then we paid, otherwise not.

Basic scenario - n^^2 messages

This assumes some level of communication between the cryptographers.

Advantages:

- Provable, information theoretic anonymity
- Security independent of relays

Disadvantages:

- Naive implementation is inefficent O(n^^2)
- May optimixations exist and are needed

Scaling by avoiding all-to-all communcation:
small amount of servers (m << n), and a lot of clients. Clients communicate only with the servers.

## Sybil attacks and defenses

**What is it:** "Sybil" is study of a patient diagnosed with multiple personality disorder (1973).

Anyone can have as many electronic personas as one has time and energy to create - The Sybil Attack

Fake identities:

- virtual nodes
- Social media bot
- Ballot stuffing
- fake reviewers
- Sockpuppets (participate in a forum with other fake personas who agree with you)
- Astroturfing (practice for an entity of presenting themselves to give a different opinion - e.g. tabacco movement against public legislators or shell "working" on renewables)

### Implications

DHTs: eclipse attacks - censor nodes, censor key-value pairs

Compromise threshold-based security (t-of-n):
creeping compromise - slowly increase t, n

Compromise consensus:
force particular decisions
rewrite history
equivocate (multiple histories if i tell different people different stories - Byzantine attack)

### Sybil defenses

Permissioned systems - only select few nodes

Strong identity

Adding artificial costs

Social network-based - relationship between the identities

Proof of Personhood

#### Stronger identities

Sign up with phone number (e.g. WhatsApp) - buy phone numbers, buy burner phones
Sign up with credit card - fake cards, fake passports
Sign up with e-mail - me@gmail.com vs me+cs438@gmail.com
ID verification - Regularory requirement (e.g. "Know your customer" - KYC); fake ID but derred by cost, jail, paper trail

Biometrics - face, fingerprints, iris, DNA.
Biggest biometric database - Aadhaar (India) - 1.38B. Mandatory database which stores an identification number tied to biometric.
China - collects DNA, and has a database.
Common Identity Repository (EU) - 350M - put all of the data together (problems with privacy)
Dpt. of Homeland Security (US) - 270M (on average saw everyone 4 times)

**Weaknesses**:

- Privacy
  - needs centralized database
  - DB encoding: password will be stored as a hash, meanwhile biometric info needs to be stored in plain. Sybil resistance - verify that the new registered fingerprint does not exist in the database already.
- Forgeability
  - Fake "fingerprints" - from a photo it is possible to forge fingerprints
  - Fake "iris"
  - Biometric synthesis - synthesize realistic data, means trusting the ML model.

#### Artificial costs

Key idea - increase the cost to Sybil identities

- Proof-of-work (bitcoin approach)
- CAPTCHA (Turing tests)
- Threshold validation
- Proof-of-stake (put money on others' trust - if i am misbehaving i will lose this money)
- Proof-of-space/storage

##### Proof-of-work

first used as anti-spam
popularized by Bitcoin

It is a crypto puzzle:
$H(data, nonce) = 000...000xxxxxxxxx$ -> find the **nonce**
0s are Proof-of-work threshold, and you need 2^^n hashes

This does not prevent an attack, just increases its costs
Also, it is not efficient and not environmentally friendly

It is more than a 1000x worse than other ideas from energy perspective.

##### Proof-of-stake

Etherium

Nodes must stake money to participate in consensus
Randomized validators, likelyhood based on stake.
If validators don't agree, if you misbehave, you get punished by loss of stake
Plutocracy: more money - more stake (problem for small cryptocurrencies)

##### Social/Trust network defenses

- PDP "Web of Trust" model
  - Alternate to PKI
  - "Key signing" parties
  - "Alice" -> Key A, "Bob" -> Key B
- PKI/Client-side TLS certificates
  - It could be company-managed in a IoT environment
  - Email-challenge
  - not great in Sybil denfense perspective
- Generic
  - SybilGuard
  - SybilLimit
  - SybilRank
- App-specific
  - SumUp...

Assumptions that these systems are making:

- Social graph
- Edges denote "trust"
- Honest region is well-connected
- There exists a "Sybil region" scenario, which has only few edges to the honest region, therefore attack edges are expensive and attack edges are rare/few.

SumUp idea:
Random walk in the graph - chances that i go out of well-connected (honest) area is very low.
Assign voting rights to the end node
Repeat
Majority of the voting rights stays in the honest region, even though there could be.

**Weaknesses**:

- basics: privacy, performance
- re-thinking the "movie plot threat" - why go into these things, when they are so complicated
  - crow-sourcing - get the majority through financial incentives, botnet
  - sparse infiltration - every single region is 1 node
  - small-scale attack

##### Sybils on Facebook

We're Facebook and trying to detect fake accounts:

AI, look for usage patterns - IP could be an indication (uzbekistant IP but accutely interested in Swiss politics), volume of usage
reporting - ineficient, not necessarily correct
connectivity - 1) who contacted who - new account reaching out to a lot of people, 2) who are you connected to who - similar age/usage

If these detections are public, the adversaries are just going to change approach so most of the time it is kept secret.

##### Proof-of-Personhood

Key intuition - link identity to "being a physical person"

Goals:

inclusion - low cost to participation (permissionless)
equality- one person, one vote (strictly)
security - against identity theft/loss and Sybils
privacy - no ID, no biometrics, etc.

Approaches:
pseudonum parties
Encointer - Co-located physical bodies - person can be at one place at one time.
Idena - "Flip" tests (Turing tests) - make a story out of pictures that makes sense. And it also prepares a flip test for others
Humanity DAO - DAO/curated list
Many others - Upala, BrightID, Good

## Review of Consensus

### Logical clocks

Lamport clock - A caused B -> C(A) < C(B)
Each message contains the logical time, receiving updates the local clock

Vector clock - C(A) < C(B) -> A caused B
Similar to G-Counter CRDT, one counter per node.

Threshold logical clock - specialized for threshold applications

#### Threshold logical clock

When a consensus is reached -> broadcast logical clock advance.

Then a threshold (quorum) of clock advances has been received -> move to the next box, even if we haven't witnessed the consensus

## Byzantine problems

### Byzantine generals problem

Some generals surround the castle, and the goal is to take the castle. They will win if they coordinate correctly - either attack or retreat.

Generals or messangers might be treacherous.

**Failure model**:

- arbitrary failures
- general (=process) may be malicious
- Generals may collude
- Network may be malicoius
- system may present conflicting info
- computations may be incorrect

**Fault**: underlying defect:

- active - injects errors in the system
- passive - latent

**Failure**: system no producing the desired result -> 1 + fault(s) made the system useless

**Fault-tolerance**: building reliability out of unreliable components

**Redundancy**: fundamental principle to build fault-tolerant systems

### Byzantine faults - Causes

Malicious actors (hacking), software bug, hardware failure

What kind of hardware failure -> network

### BFT Consensus

Key properties:
Safety - all nodes agree on a (single) decision
Liveness - eventually something is decided

Paxos >= 2f + 1

Why does it not work for BFT?:

Byzantine model:
Malicious node "X"
Malicious network

Delay the network long enough such that 2/3 acceptors receives proposal. Other proposer does the same, but only one acceptor node is overlapping. Then attack could be carried out by the overlapping node and break safety - 2 different values were agreed on.

Therefore 2f + 1 is not strong enough.

BFT: n >= 3f + 1
No matter what there will be at least 1 honest node in the intersection.
(even though there is no assumption about who's honest)

How to decide on n? - cost analysis

Sometimes people will accept Byzantine faults because the cost of the chance of introducing a bug with the implementation of BFT.

## Permissionless consensus (Bitcoin and Proof-of-work)

### Bitcoin - key ideas

Proof-of-work:

- "miners" solve computational puzzles (hash with N leading zeros) => Computational power = Hash rate (H/s)
- Puzzle difficulty is adjusted to keep block rate (roughly) constant - around 10min. It compensates for changes in mining power.

10min - ensures that everyone has received a block n, before there is a chance for anyone to mine block n+1.

### Bitcoin assumptions

Threshold assumption - majority of mining power is honest (you cannot corrupt more than 50%). This means it is independent fo the number of nodes

Keep the heaviest chain (that has consumed the most computational power). This is because of the network partitions, give weight to the network that has done more work.
transient safety violations - e.g. forks, reversed transactions are OK.
Eventually forks will be resolved (based on the expended work) <- All of this is highly probabilistic

Probabilistic finality - 6 blocks (1h) - instead of saying "we have the transaction, it's effective now"; Bitcoin waits for 6 blocks, which comes from probability of a fork happening.

Economic incentive compatibility - bitcoin gives economic incetives to miners

Safety assumption - assuming that messages arrive in very short time - **synchronicity**

## Skipped bitcoin and ethereum

## Advanced Blockchain architectures

### Limitations of mainstream blockchain platforms

Weak finality - probabilistic (~1h for Bitcoin)

Transaction throughput and cost - few TPS

Transaction commit latencry

Fairness - Power distributed by investment, not by people (a lot of hw - wins proof of work, a lot of money - wins proof of stake)

Energy waste (PoW)

Privacy - TX identities, amounts, data, computations

Following blockchains efficiently (to verify it, i need to keep the whole blockchain, or verfied cache)

Bridging between chains

Governance - upgrade, replace

### Current state of throughput

Bitcoin: 4-7 TPS (transactions per second) (around 2400-10000 transactions per block)

Ethereum: 20-30 TPS

VISA: 1500-4000 TPS (pre-2020) and ~8000 TPS (now, and says that they can scale up to 65,000TPS)

Solutions:
Sharding it,
Speed up the blockchain algorithm,
Increase the block size,
Have a smaller blockchain where the transactions are done

### Scaling throughput - Approaches

Tweaks:

- scale up the nodes (faster links)
- Reduce block time (bitcoin's 10min, ethereum 15s)
- Make use of wasted effort (when the block is not on the longest chain, and gets lost)
  - use orphaned/competing heads in blockchain
  - Turn blockchain into a DAG (there could be double spending between parallel blocks but there are algorithms to stop it)

Bypassing blockcahin / batching transaactions:

- payment channels - e.g. Lightning network
- Layer 2 chains - separate consensus mechanism
  - rapi transactions, instant finality, periodically committed to main chain
  - ZK (zero-knowledge proofs) rollups: verify transaction history, not just hash
  - optimistic rollups: claim, can be challenged during time window
- Side chains (-> bridging problem - how to convert my currency to the other)

Rethinking consensus:

- Hybrid consensus mechanisms - Bitcoin-NG, ByzCoin
  - Can we achieve (permissionless) performance closer to PBFT?
- Sharding - OmniLedger, Cardano (Ouroboros), Ethereum (past roadmap)
  - can we scale up?

#### Bitcoin-NG (Next Generation)

Bitcoin transactions are very much included in the block (because of the merkle tree). Uses PoW for transactions

Bitcoin-NG still uses the PoW, but it is used for the election of the leader.
PubKey is included in NG Block, and it is used to generate micro-blocks of transactions + signatures, until the main block gets created again.
if the leader is acting up, and leader 2 can discard that, and leader 3 can follow 2's decision
Problems:

- because of the insentive to have transactions as fast as possible
- maximum value problem because we have a dictator
- the new leader can ignore previous TXs, so there is an insentive that past leader pays new leader
- there can be DoS attack against the leader

PoW becomes a form of leader election
Transaction processing is separate from PoW
Incentives need to be adjusted

Pro: higher TPS

Con: "temporary dictator" (DoS-able)

#### ByzCoin

Built on Bitcoin-NG, and tries to avoid "temporary dictator"

Form a consensus committee out of 100-1000 last PoW winners (it's not a huge amount of nodes, and does fair amout of sampling from the system (more NSA-proof))

Operate with BFT consensus within the committee (e.g. PBFT)

PoW chain is for the committee members
PBFT chain is for the transactions - signed (quorum signed) micro-blocks

Challenges:

- How do clients know and verify which micro-blocks were committed?
  - collective signing (threshold of committee)
- How do you rotate the committee?
  - Option 1: via PBFT commit a transaction of "new transaction" => guarantees safety (there is no ambiguity what is the new committee) with large enough committee.
    - problem - committee is small or likely to go offline
  - Option 2: via PoW alone (you could go through the last 1000ish blocks to find all the pubkeys, but it needs a lot of state) => guarantees liveness

Attack example: old committee selects itself

#### Sharding

Problem: no "scale out" in blockchain, everyone processes everything

Desired state: more miners = more aggregate capacity

Potential solution: shard across UTXO

UTXOs are assigned to different shards.
If I am only doing the TX in Shard A, the miners in only Shard A can execute it.

Challenges:

- how big should a shard be?
  - To distribute the nodes in the shard we need something verifiably random
- cross-shard transactions
- threat: shard takeover

##### Cross-shard transactions

- two-phase transaction lock
- request all shards to lock a TX, then execute
- on failure/lack of responses - abort
- on success - commit

Problems:
multiple miners need the same TX - double-spend problem, then it would be either aborted or already locked
if one of the shards stop responding (the lock was sent out and it stopped responding)

If shards are untrusted:
Time lock
Revert unless TX goes through
This is much more complex protocol, guarantees safety + liveness

### Approaches to energy efficiency

**Proof of Burn** - based on other PoW blockchains (the motivation behind PoW is making it costly to do Sybil attack).
Idea behind Proof of Burn - create unspendable outputs, which basically is burning the coin

**Proof of Storage** - Chia - (hard disks instead of electricity) - solving a problem which requires a lot of space instead of mathematical problem
One of the approaches - mathematical pebbles
Storing some useful data, and at any point you have to be able to prove that you have the data
Or having a ton of stuff in RAM.

**Proof of Sequential Work** - Verifiable Delay Functions (VDF). Create a sequence of operations and verify that they were done in order.

**Proof of Elapsed Time** - spend time waiting. Requires specific hw for TEE

**Proof of Stake** - most deployed solution

#### Proof of Stake

If I misbehave, I lose my stake, otherwise I get rewarded.

How to form a consensus group?
Ethereum: RANDAO (smart contracts which create some randomness). People will create some hashes, and put money in, and after some time people are forced to reveal the numbers under the hashes (or they lose money). And these numbers are put together and used as a seed.

Algorand:

- random sample of stakeholders
- use Verifiable Random Funciton to genetrate a unique "lotery ticket" per node, per round
- Ticket "wins" if below a threshold value. A node knows if it won (above the threshold), or not, it is private
- Reveal winning ticket along with consensus vote (this prevents DoS attack)

Why change acnsensus group at every block?

- protect against fast, adaptive adversary
- prevents DoS attacks, nodes hacking

### Following blockchains efficiently - Skipchains

Problem: retrieving information from a blockchain requires following it actively, fully

Solution:

- ByzCoin-like collective signatures
- add "forward links" in addition to backward (hash) links (such that we can traverse the blockchain from the first to last)

Sill requires O(n)

How can we do better?

Blocks reference previous blocks, and skip links which are of different levels.
This skip list is in each block, and you can traverse the blocks at any speed.
Multi-level links enable O(log n) retrieval

There is the only time when you need to go to specific node, is when the committee changes, where the signatures change.
In principle, this allows you to go very fast.

This can be used for reliable software distribution (connect to the internet sometimes and get the latest version).
