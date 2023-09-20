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

Techniques:

- Transpositions - e.g. Spartan scytacles which reorders the message letters such that it is known by some key (stick with a belt)
- substitutions - e.g. Caesar cipher (letter is moved in an alphabet), ROT13 (shifted by 13 positions, so it is half of alphabet)
