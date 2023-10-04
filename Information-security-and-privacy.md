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
