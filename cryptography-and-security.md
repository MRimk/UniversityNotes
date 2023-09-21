<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

# Cryptography and Security

## Ancient cryptography

### Scope of Cyptography

Now it is basically any device that uses some encoding.

In prehistory it was to preserve confidentiality/privacy.

Modern cryptography is public and interceptable, so confidentiality is a problem. The main problem of modern telephony is authetication of the user/access control. There are also problems such as detection of malicious modificaiton, data authetification, non-repudiation (no stepping back/denying a completed action), access control, timestamping, fair exchange, etc.

### Notions

The differenece between coding and cryptography is that crypto has malicious adversary whereas coding has some noise or nature that could affect reliable communication (= dummy adversary).

Cryptanalysis is a theory of security analysis of cryptography systems.

To cryptanalyze a cryptosystem means to probe or to disprove the security (but does not necessarily mean to break it). Breaking is just proving the insecurity.

### Secure communication problems

1. Nobody else can read the message (sent over an insecure channel) - confidentiality
2. Receiver must get the same message (integrity) as it was sent by the sender
3. Only the right receiver should get the message - authetification

### Symmetric encryption

Assume: confidentiality.

Sender will use same key to compute MAC (message authentification code) and the receiver will decode the MAC. This ensures authentification and integrity.

Symmetric encryption algorithms are very efficient and quick.

Problem is to have the same key.

### Establishing Symmetric key - Key Agreement Protocol

Key should be made sure that it comes from the right receiver (is not modified, not known to adversary).

Only assume authetication, integrity. Because the confidentiality does not necessarily matter during the exchange.

### Public-key cryptosystem

Assume authentication and integrity so that it is not replaced by the adversary.

Receiver creates generator to give public key to sender.

Receiver uses secret to decode the message that is encrypted by their pub key.

### Digital signature

It is the reversed PK cryptosystem. Server signs the message with their secret and receiver verifies message with the sender's pub key.

Assume pub key is transfered in autheticated and integrity preserved channel.

### Example of TLS (slide 24)

Browser already has some authorities.

When server is created it sends its pub key to CA to sign it, and then server sends the message to client signed with its private key. Client verifies message with authority-given server's public key (authority signs the public key).

## Prehistory

Hieroglyphs were understood only by some people.

### Techniques

#### Transpositions

e.g. Spartan scytacles which reorders the message letters such that it is known by some key (stick with a belt)

#### Substitutions

e.g. Caesar cipher (letter is moved in an alphabet), ROT13 (shifted by 13 positions, so it is half of alphabet), random substitution table - a lot of permutations 26! - to break this we can do frequency analysis on 1, 2, or 3 consecutive letters.

#### Continuous permutation

Vigenere cipher - take a message without spaces and take a key (e.g. ABC) and continuously apply to each letter. E.g. "this" + "ABC" = t+0, h+1, i+2, s+0. One of the first cyphers with a secret key. The continuous permutation messes up the statistical analysis.

- column-dependent substitution - write out the message into the key-length amount of columns and then apply statistical analysis.
- Also statistical analysis - if there is a repeating trigram. (e.g. 313 chars, 26 possible letters, 5 occurances of same trigram). Calculation of k-tuples of elements in a set of size z: z^k. Number of possible subsets of t elements in a set of size n: nCt. This leads to binomial distribution: probability to pick the same item u exactly t times that has a probability p is nCt \* p^t \* (1-p)^(n-t). So there are n=311 (length - 2)possible trigrams. Each trigram has an independent probability of appearing 1/p = 26^3 = 17576. Approximate binomial distribution wiht poisson's distribution because n \* p is small, and we get that the probability to get 5 occurances is very low. The differences of occurance locations are multiples of 5, so the key should be 5. So it is 5 columns.
- Index of Coincidence can also be used. The formula is sum c in Z nc(nc-1)/n(n-1)
- Expected Index of Coincidence - Sum c in Z fc^2 if all xi have independent distrbution with frequency table fc
- Index of column can be used to verify a guess of the key length (language should be known because it differs). Index in English as n -> inf, is -> 0.065, so if it close for the column, then we know that the key length is correct

## Pre-Modern Industrial Cyptography

### Enigma

Electro-mechanical encryption device (typewriter) which could be plugged into radio transmiter.

It was patented in 1918, so the information about the device was public, but the secret was inputted in the device to encrypt information.

It was used by the German army WW2.

There were preliminary attacks by polish mathematician Rejewski in 1932 but then they were invaded, so transfered information to France, which was also invaded, so it was transfered to UK.

There was an "industrial" attack from Bletchley Park (~2000 messages per day) during WW2. They built computers to automatize breaking the messages, because mathematics were understood but required a lot of checking.

The key is connected to the plugboard plug, and then the signal goes to the rotors (through 1st, 2nd, 3rd, 3rd, 2nd, 1st), and back to plugboard, back to the light. Each time the key is pressed, the rotor will move. First rotos moves with each letter, 2nd every full 1st rotation, etc.

Encryption and decryption is symmetric as long as you start from the same condition (due to electrical signal symmetry (N.B. my idea))

Initial state is the key. There are 5 different rotors available, so the 3 chosen rotors and their starting positions, and wires plugged in the plugboard.

#### Definitions

Fixed point - Given a permution sigma over Z, a fixed point is an element x in Z such that sigma(x) = x (no change)

Involution over Z is a permutation sigma of Z such that sigma(sigma(x)) = x for all x. (so the reflector after last rotor is that, plugboard is that)

Rotor sigma defines a set of sermutations sigma0, ..., sigma25 over Z. The rotor in position i implements permutation sigmai, such that sigmai = p^i o sigma o p^-i

Secret key:

- sigma (involution made of 6 pairs)
- ordered choice of alpha, beta gamma in S of pairwise different permutations
- a number a

Encryption: yi = σ −1 ◦ αi−1 ◦ βi−1 ◦ γi−1 ◦ π ◦ γi3 ◦ βi2 ◦ αi1 ◦ σ(xi)
where i3 i2 i1 are the last three digits of the basis 26
numeration of i + a.

Key entropy of Enigma:

Number of involutions:
26 C 14 \* 11 \* 9 \* 7 \* ... \* 1 ~= 2^37
(14 is fixed points are the leftover plugs that are not connected by the 6 cables)
(11 is available positions to connect the other end of the cable, then 9, then 7, then ...)

Number of choices for the rotors:
5 \* 4 \* 3 = 60

Number of initial positions: 2^14

It is 57 bits.

## Laws of Modern Cryptography

### Law 1: the Kerckhoffs Principle

Security should not rely on the secrecy of the cryptosystem itself

WHY? - the adversary may get some information about the system (e.g. reverse engineer)
WHAT DOES IT MEAN? - security analysis starts with the assumption that adversary knows the cryptosystem
DOES NOT MEAN - cryptosystem must be public.
