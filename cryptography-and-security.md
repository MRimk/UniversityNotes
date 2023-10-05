<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

---

header-includes:

- \usepackage{algorithm2e}

---

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

Encryption: $y_i = σ_{−1} ◦ α_{i−1} ◦ β_{i−1} ◦ γ_{i−1} ◦ π ◦ γ_{i3} ◦ β_{i2} ◦ α_{i1} ◦ σ_{xi}$
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

### Law 2: scalability - the n^2 problem

in a network of n users, there is a number of potential pairs of users within the order of magnitude of n^2

We cannot assume that every pair of users share a secret key
We must find a way for any pair of users to establish a secret key

### Law 3: Moore law

the speed of CPUs doubles ever 18-24 months.

We should wonder how long a system must remain secure
We must estimate the speed of CPU at the end of its period

### 128-bit key

Possible key combinations - 2^128 (39 digit number)

It is impossible to do an exchaustive search.

In 2007, a standard PC could test 10^6 keys per second
To run exhaustive search within 14 billion years we need 770 000 bilion 2007-PCs

if the Moore law goes on, a single 2215-PC will do it in a second

## Two Revolutions

Communication - information theory, mass communication (radio) -> we need standard crypto

Computing - computer science, automata -> adversaries have more power

## XOR

Bit-wise exclusive or.

Due to its properties forms a commutative group.

### Vernam cipther

Message is passed through a key with xor, and then decrypted with the same key with xor. $(X \oplus K) \oplus K = X \oplus (K \oplus K)$

This cipher was tried to be published in 1918 (only published in 1926), because it was deemed that the WW is over.

We use a uniformly distributed random key K.
Every message X requires a new K of same size (one-time pad)

Q: When is it insecure?

1. When using the same key twice: $Y_1 = X_1 \oplus K$ and $Y_2 = X_2 \oplus K$. We xor those numbers and we get (by applying distributivity and commutativity) xor of plaintext: $Y_1 \oplus Y_2 = X_1 \oplus X_2$.
   The same way it could be used for visual cryptography. And in visual crypto it can be seen clearer why it is possible to deduce what are those plaintexts (plain images) when they are xor'ed.
2. if K is smaller than X. only the left part wil be encrypted and the right part will stay the same.
3. if K is not uniformly distributed. $Pr[K = k] high \implies Pr[X = y \oplus k] high$

Due to one-time use, in most cases it does not make sense to use this.
But provides perfect security

Makes sense to prepare emergency communication (red telephone) - keys are exchanged (through slow channels) before the messages to transmit are known

bad news for other applications - there is essentially no better cipher with this strong security property

#### Intuition on perfect security

if the adversary gets Y = y then for any x:
$$Pr[X = x | Y = y] = Pr[X = x | X \oplus K = y] = Pr[X = x]$$

because $X$ and $X \oplus K$ are statisticaly independent $\implies$ the adversary gets no information about X in knowing that Y = y

#### Abelian group

Set of G together with a mapping from G x G to G which maps (a,b) to an element denoted a + b

1. [closure]
2. [associativity]
3. [neutral element]
4. [invertability]
5. [commutativity] (only in Abelian groups)

E.g.
$\Z$ with regular addition
$\{0, 1\}^2$ with $\oplus$
$\{0,1,...,n-1\}$ with $(a,b) \rightarrowtail \begin{cases}
    a+b\ \text{if}\ a+b < n \\
    a+b-n\ otherwise
\end{cases}$

#### Useful lemma to prove security

**Lemma**: Let X and K be two independent random variables in a given group. If K is uniformly distributed, then Y = K + X is uniformly distributed and independent from X.

**Proof**
For any x and y:
$$Pr[X = x, Y = y] = Pr[X = x, K = y - x]$$

$$= Pr[X=x] \times Pr[K = y - x]$$

$$= Pr[X=x] \frac{1}{\# group}$$

$$Pr[Y=y] = \sum_x Pr[X=x, Y=y] = \frac{1}{\# group}$$

#### Theorem

**Theorem** - For any distribution of X over G, Y is independent from X and uniformly distributed
(perfect secrecy)

### Information theory

Entropy - (used in this course) number of bits.
But there is the Shannon Entropy - amount of information you have in a random variable.

### Perfect Secrecy

**Definition**: Perfect secrecy means that the a posteriori distribution of the plaintext of X after we know the ciphertext Y is equal to the a priori distribution of the plaintext:
$\forall x,y \ Pr[Y=y] \ne 0 \implies Pr[X=x | Y =y] = Pr[X=x]$

Also, perfect secrecy is equivalent to statistic independence of X and Y
Or, is equivalent to H(X|Y) = H(X)

**Theorem**: For any distribution of the plaintext, the generalized Vernam cipher provides perfect secrecy.

**Shannon theory** - perfect secrecy implies $H(K) \ge H(X)$
Or: Perfect secrecy implies that the support of K is at least as large as the support of X.

#### Negative side of Shannon Theorem

If we want ot achieve perfect secrecy, the number of possible keys must be at least as large as the number of possible plaintexts

**Theorem**: perfect secrecy implies that X has a finite support.
$\#support(X) \le \frac{1}{p}$, where $p = Pr [Y=y] \ne 0$

Intuition - length of the cipher text will give some information on the plaintext. E.g. 1TB plaintext will be represented by approx 1TB ciphertext

#### Summary of Shannon results

We have mathematically formalized the notion of perfect strategy
Vernam Cipher achieves perfect secrecy
Despite Vernam Cipher is expensive, there is no cheaper alternative.

The **Complexity theory** is missing, since the perfect secrecy is impractical.

## Diffie-Hellman Cryptography

### Arithmetics on $\Z_n$

**Theorem** - every integer n can be uniquely writen as a unit times product of prime numbers $n = u \times p^{\alpha_1}_1 \times ... \times p^{\alpha_r}_r $. Where $u = \plusmn 1$

Two notations of "mod":

- w/o parenthesis x mod n is an operation
- with parenthesis $a \equiv b (mod\ n)$ is an equivalence relation.

$\Z_n = \{0, 1, ..., n-1\}$
Addition: $a \boxplus b = (a+b)\ mod\ n $
Multiplication: $a \boxtimes b = (a \times b)\ mod\ n$
Both are associative, closed, has neutral elements, invertable (for $\boxplus$) and distributed.
Notation can be $\Z/n\Z$

**Abelian group** is a group that also has commutativity.

**Group homomorphism** - given two groups $(G_1, \times_1)$ and $(G_2, \times_2)$ a mapping f from $G_1$ to $G_2$ is a group homomorphism if for any $a, b \in G_1$: $f(a \times_1 b) = f(a) \times_2 f(b)$
**Isomorphism** - group homomorphism which is bijective is called an isomorphism. _ismorphism = change pf notation_

**Subroupts theorem** - if H is a subgroup of $\Z$ and $H \ne \{0\}$, then $H = n\Z$ where n is the smallest positive element of H.
Proof:

- let $a \in H$ and write $a = qn + r$ with $q, r \in \Z$ and $0 \le r < n$ (Euclidean division)
- since H is a group and $a, n \in H$ we have $r = a - qn \in H$
- since $0 \le r < n$ nad n is the smallest positive element of H, we must have r = 0, thus $a = qn \in n\Z$
- therefore $H \subset n\Z$
- conversely, rn must be in H for all $r ∈ \Z$, therefore $H = n\Z$

**Generator** - givent a group (G,.)m an element g generates/spans a $\langle g \rangle = \{..., g^{-2}, g^{-1}, g^0, g^1, ...\}$

**Definition** If (G,.) is a group and if G is a finite set, then the cardinality of G is called the group **order**.
If g generates a subgroup of order n, then n is colled the order of g

**Preposition** - the order of g is the smallest i > 0 s.t. $g^i = 1$
Proof:

- the set of all $i \in \Z$ s.t. $g^i = 1$ is a subgroup of $\Z$ (preimage of subgroup {1} by group homomorphism $i \rightarrowtail g^i$)
- it must be of form $n\Z$ where n is the smallest among all i > 0
- $\{1, g, g^2, ..., g^{n-1}\}$ is a non-repeating exhaustive list of all $\langle g \rangle$ elements.

_Consequence_
if g is of order n:

- $\langle g \rangle = \{..., g^{-2}, g^{-1}, g^0, g^1, ...\}$
- $\forall i g^i = 1 \lrArr n|i$
- $\forall i,j\ g^i = g^j \lrArr i \equiv j (mod\ n)$

**Power group** given $(G, *)$ and I, consider $G^I$ and $(a*i)_{i \in I} \times (b*i)_{i \in I} = (a_i * b_i)_{i \in I}$

**Quotient Group** - given a commutative group G and a subgroup H, consider the set G/H of classes for congruence module H with the law induced by +.

- a and b in G are said to be congruent modulp H if $b -a \in H$, notation $a \equiv b (mod\ H)$
- the relation "... is congruent to ... modulo H" is an equivalence relation (refl, sym, trans)
- notation: for $a \in G, a+H$ is the set of all G elemenet which can be written as $a +h$ for some $h \in H$ (elements congruent to a)
- every class of equivalence can be written as $a + H$ for some $a \in G$ a is called _representative_ for the class

Quotient example: Z/6Z
$Z/H = \{H, 1+H, 2+H, 3+H, 4+H, 5+H\}$

**Lagrange theorem** - in any finite group, the order of any element is a factor of the order of the group.
_Consequence_: $\forall g \in G\ g^{\#G} = 1$

**Theorem** - if a group has a prime order, all elements (except 1) are generators.

### Diffie-Hellman Key Agrreement Protocol

Assume a group generated by some g (g is public)

Alice picks x at random, X is $g^x$, sends x to Bob.
Bob picks y at random, computes Y is $g^y$, sends y to Alice.
Alice uses $K = Y^x$, Bob uses $K = X^y$
$(K = g^{xy})$

security requirement: given $(g, g^x, g^y)$, it must be hard to compute $g^{xy}$ (**Computational Diffie-Hellman Problem**)

#### Using the Diffie-Hellman key agreement protocol

Allows to set up a secret key over a public channel (assumening authetification)

No further need to set up pre-shared keys: sets up keys when needed -> pub key cryptography

### Algorithms for Big Numbers

**Monoid** is a set group without invertability.

We want to multiple a monoid element (a = 12) by an integer (n = 100101 in binary):
12 x 100101 - we use powers of 2.
Multiplication by 2 consistes of additing ot itself - multiplication by 2^i consists of multiplying i times by 2.

Double-and-add from left to right or right to left is O(l) complexity of monoid additions.

The equivalent for squaring is multiplying.

### $\Z_n$ - Ring of Residues Modulo n

Ring has Abelian group properties as well as closure, associativity, neutral element, distributivity, and commutative rings have commutativity.

Group of units:

- not every element x in a ring R has an inverse for the multiplication
- we denote R\* the set of elements having a multiplicative inverse, which are **units**
- group of units is denoted as R\*

subgroup - subset of a group stable by group law and inversion. Ideal - subgroup of a ring stable by multiplication by any ring element.

Spanned structure - set of all values generated by structure operations

product structure - set of pairs with inverited structure operations

#### $\Z$ is a commutative ring

#### Example: $\Z[X]$

Z[X] is a set of polynomials with coefficients in Z.

It is a commutative ring, with neutral element would be 0.

#### Verifying multiplication

Sum of first number of digits mod 9 times sum of second number digits mod 9, is the product digits sum mod 9.

Mod 9 works because 10 to any power reduces to 1.

#### Example: the ring of resudues mod n

$Z_n = \{0, 1, 2, 3, ... , n-1\}$

Cerebral $\Z n$:

- nZ is an ideal of Z (with laws mult and add)
- we can do the quotient Z/nZ of Z by nZ
- congruence modulo nZ is written: $a \equiv b (mod n) \lrArr a\ mod\ n = b\ mod\ n$

$Z_n$ tips:

- for any polynomial P(x) in Z[x] and any a, n in Z we have $P(a) mod\ n = P(a\ mod\ n) mod\ n$ - we can put "mod n" reductions in the ground floor.
- if x has order m in Zn\* then for any i in Z: $x^i\ mod\ n = x^{i\ mod\ m} mod\ n$, so we can put "mod m" reductions in the upper floor.

##### Exercise

$Z_{15}$ has order 15.

- we have $\langle 5\rangle = \{0, 5, 10\}$
  - this is a subgroup of order 3
  - 6 has order 3 in $Z_{15}$
- in $Z_{15}$: $\langle 2\rangle = \{0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13\}$
  - 2 has the order 15, so 2 is a generator
- we have $\langle 1\rangle = Z_{15}$
- $Z_{15}^* = \{1,2,4,7,8,11,13,14\}$ (3 is not there because it is not invertible because (3r - 15q = 3r mod 15 != 1), same is for 5 and 6. Intuition 3 and 5 are factors of 15)
- in $Z_{15}^*$ 2 has the order 4: $\langle 2\rangle = \{0, 2, 4, 6, 8\}$

#### $Z_n$ computations

Efficiently computable operations:

- addtion: (a+b) mod n
- multiplication: (a \* b) mod n (double-and-add)
- modulo: a mod n (Euclidian division)
- inverse: $a^{-1} mod\ n$ when gcd(a, n) = 1
- power: $a^e$ mod n (for e integer only) (square-and-multiply)

And remaining problem is extracting the roots

##### Euclidean division

x = qy + r
algorithm runs in $O(l^2)$

##### Modular Inversion

**Theorem** x in $Z_n$ is inveritible if and only if gcd(x,n) = 1.
(this is why 3, 5 were not inverses in Z15)

**Euclid algorithm** is used to calculate gcd.
Why does it work? -
Why does it terminate? - Euclidean division and subtraction decreases the number so it will become 0 at some point.
Why does it come out with GCD? - set of common dividers of initial numbers is the same as next step euclidean algorithm numbers.

Running time is quadratic to the length of numbers in bits

**Extended Euclid algorithm** is used to calculate d, u, v, that d = au + bv = gcd(a,b).

#### Orders of group

**Element order**: n is the smallest positive such that $x^n = 1$
n is such that $x^i = 1 \lrArr (n \text{ divides } i)$

**Group order**:
$G = \{i ∈ Z; ∀x ∈ G\ x^i = 1\}$
$\lambda$ is called the exponent of G, where it is the smallest positive such that $\forall x \in G, x^\lambda = 1$
Note: $\#G \in \lambda Z$ so $\lambda$ is a factor of #G, so $\forall x \in G \text{ order(x) }| \lambda | \#G$
λ is the lcm of all order(x), x ∈ G

**Orders in $Z_m^*$**
$Z_m^*$ is of order φ(m) (example: $Z_35^*$ is of order 24)
$Z_m^*$ is of exponent λ(m) (example: $Z_35^*$ is of exponent 12)

for $m = p_1^{α_1} × · · · × p_r^{α_r}$ with pairwise different prime numbers $p_1 , . . . , p_r$ , we have

φ(m)=(p1 − 1)p1α1 −1 × · · · × (pr − 1)prαr −1
λ(m)= lcm λ(p1α1 ), · · · , λ(prαr )

**application**: if n is hard to factor, we can still find generators: find prime factors up to some bound B

#### Picking a generator in a cyclic group with known order

This algorith is probabilistic with a bound of $\text{Pr[output g not generator]} \le \frac{1}{B\log B}\log B$

$\text{Pr[not generator | passed]} \le \frac{1}{B}(r-s) \le \frac{\log q}{B\log B} \le \frac{\log n}{B\log B}$
Where B is a bound for small factors, n is the order. (r-s) is ... and q is the remainder of incomplete factorization

### $\Z_p$ Field

**Field** is a ring where every possible element that is not 0, is invertible.

Example fields: rational, real, complex numbers.
We will use $Z_p$ for p prime

**Theorem** - $\Z_p$ structure

1. $Z_p^* = \{1, ..., p-1\}$ (GCD = 1, therefore they are invertable)
2. (Little Fermat Theorem) for any $x \in Z_p^*$ we have $x^{p-1} = 1 (mod\ p)$ (Lagrange theorem)
3. $Z_p^*$ is a cyclic group. So there exist g such that: $Z_p^* = \{g^0, g^1, g^2\ mod\ p,  .., g^{p-2}\ mod\ p\}$

subgroup of $\langle g \rangle \subseteq Z_p^*$ of prime order q (if not, then it would be just even numbers): $\langle g \rangle = \{1, g, .., g^{q-1} \} \lrarr \{0, 1, ..., q-1\} \subseteq Z_p^*$

Example: SSH2 parameters

#### The discrete logarithm problem

**Definition**: The DL problem, relative to Setup, is hard if for any (probabilistic polynomial-time) algrorithm A, the probability that the follong game returns 1 is negl($\lambda$):

```
DL(λ):
1: Setup(1^λ ) → (group, q, g)
2: pick x ∈ Zq
3: X ← g^x
4: A(group, q, g, X) → x'
5: return 1_X=g^x′
```

Negligible function - the output is very small - goes to 0 faster than any inverse of polynomial.

Examples of groups:
$Z_n$ - dividing by g is easy because the operations are easy
$Z_p^*$ - believed to be hard (not proven), could be easy if there is extra information
over an elliptic curve - believed to be hard

The notion of game:
Game(security parameter):
1: setup of parameters
2: initialization of the game
3: A(what he should know) -> result
4: return 1 (on winning condition)

Advantage of A:
Adv(security parameter) = Pr[Game -> 1]

Security:
$\forall$PPT Adv = negl

Some facts about DL Problem:

- it is easy on quantum computer - Shor algorithm (quasilinear time)
- easy if n has only small prime factors (e.g. 2^100) - Pohlig-Hellman algorithm -> that is why n is preferred to be prime number
- best algorithm for a subgroup $Z_p^*$ with n and p prime:
  - General Number Field Sieve (GNFS) with complexity e^(equiv to const \* log n \* log log n) <- smaller than exponential; but if n is large enough
  - This is mostly precomputation (without X)
  - the computation from y (after precomputation) takes similar time but smaller by a constant in exponent
- Generig algorithms $\O(\sqrt{n})$
  - baby-step giant-step algorithm
  - Pollard p algorithm

#### Baby-step giant-step algorithm

Be given some x and know which power of g it is.
Take a giant step - size of l = $\lceil \sqrt{B} \rceil$
for l steps insert (g^il, i) into hashtable

for l steps
compute z = Xg^-j
if we have a (z,i) in the hash table then
yielf x = il +j and stop

This means that this algorithm is O(l) = $O(\sqrt{B})$

Pollar p algorithm is also in similar complexity.

#### Attacks based on precomputation

for example for p length of 512 bits precomputation (on 1 core) will take 10.2 years, and attack (on 1 core) will take 10 minutes.
whereas 1024 bits, precomputation 45 million years, and attack 30 days.

SSH2 uses a fixed p of 1024 bits.

### Diffie-Hellman key agreement protocol

Both compute K=g^xy.

Adversary knows the group, g, and all messages exchanged - X, Y (g^x, g^y). Computational Diffie-Hellman Problem.

#### Unavoidable active attack

MITM attack:
Eve replaces the communication with their key and runs Diffie-Hellman with Alice, Bob and they will not know that they are talking to Eve.

It is not avoidable, but all other attacks, where adversary is passive should be avoided.

Diffie-Hellman shall resist to passive attack, so must be computationally hard.

#### Computational Diffie-Hellman problem

CDH(λ):
1: Setup(1^λ) → (group, q, g)
2: pick x, y ∈ Zq
3: X ← g^x , Y ← g^y
4: A(group, q, g, X , Y ) → K
5: return 1 if K=g^xy

The goal of this game is to find K where K = g^xy

hardness of this problem requires the Discrete Logarithm Problem to be hard
Examples:
subgroup of $Z_p^*$ of prime order q
elliptic curve

#### CDH hard $\implies$ DL hard

- assume CDH is hard
- to prove DL hardness, consider DL algorithm A
- construct B, s.t. A wins DL $\implies$ B wins CDH: Pr[DL -> 1] $\le$ Pr[Modified CDH -> 1] = negl
- $X = g^{x'} \implies K = Y^{x'} = g^{yx'} = X^y = g^{xy}$

#### Decisional Diffie-Hellman problem

there is an extra input to the game - bit b.

if the bit is 1, z is xy, otherwise z is totally random number.
The game is for the adversary to find out when the bit is 0 or 1, which means that the goal is for them to not distinguish from these cases:

Adv($\lambda$) = Pr[DDH($\lambda$, 1) -> 1] - Pr[DDH($\lambda$, 0) -> 1] = negl($\lambda$)

#### DDH hard $\implies$ CDH hard

assume DDH is hard
consider C(group,q,g,X,Y,Z):
pick x' in $Z_q$
return 1 if X=g^x', Z=Y^x'

negl = Adv C = Pr[DDHC (1) → 1]−Pr[DDHC (0) → 1] = 1/q - 1/q^2 ~ 1/q

hence 1/q = negl

transition from CDH game to DDH game.
transformation:
B(group, q,g,X,Y,Z):
run A(group,g,X,Y) -> K
return 1 if K=Z

DDH in B (1) -> 1 is equivalent to CDH in A -> 1

Pr[DDH in B (1) → 1] = Pr[CDH in A → 1]

Pr[DDH in B (0) → 1] = 1/q = negl

hence Adv B ($\lambda$) = Adv A ($\lambda$) - negl
we know that Adv B (λ) = negl(λ) (since DDH is hard)
hence Pr[A wins] = negl(λ)

#### DDH easy case of a group whose order has a smooth factor

That is why we need prime factors.
