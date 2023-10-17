<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

# Information Security and Privacy

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
