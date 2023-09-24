<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

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
