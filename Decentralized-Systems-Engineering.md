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
