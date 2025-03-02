# Fault Tolerant Quantum Computing

## Organization

Mathias Soeken - Microsoft employee now

Send email to [mathias.soeken@outlook.com](mailto:mathias.soeken@outlook.com) for him to know if I am taking the course.

At the end of the course, we should be able to implement something from the course. Projects will be released around in a month.

### Goal

Explore how to execute quantum algorithms on quantum computers.

Quantum algorithms <--> Quantum computers

Since both algorithms and computers are black boxes.

**Quantum algorithm** is assumed to already exist. It exploits quantum mechanics to achieve (much) better computational complexity than classical computing. E.g. factoring or Grover algorithm (- solving optimzation problem, which is provably faster by quadratic), or simulation (exponentially faster)

**Quantum computers** are built out of qubits. And qubits can be made in various ways.

## Quantum computers challenges

**Quantum computers are slow and erronious**:

Classical computer's CPU:

- elementary instruction: RISC CPU instruction, e.g. ADD (of 64-bit numbers)
- time: takes 10^^{-9} (1GHz)
- error rate: like 10^^{-9} or 10^^{-10} => We don't think about error rates.

Example optimistics QPU (future example, not even current):

- elementary instruction: XOR of 2 bits.
- time: depends on technology, but it could be 10^^{-3} or 10^^{-6}s (in superconducting or spin qubits). So already several orders slower with way smaller instruction. This is due to engineering problem or physical limitations.
- error rate: 10^^{-4} (realistic to have in the future) to 10^^{-6} (optimistic case)

Now, say we want to build 64 bit addition operation in QPU: we would need for every bit 15 instructions => 960 QPU instructions (optimistic), and they would be on 128 qubits.

So this means, every 10 add instructions, something would fail. This is very not possible.

This is why **Quantum error correction** is important but makes it even slower.

Using **QEC** we make logical instructions from physical instructions. Example for XOR:

- we will have slower speed -> could be few secs.
- we will use more qubits (for redundancy) -> 10,000 - 100,000 qubits (just for one instruction)
- BUT we can get any error rate, even close to classical computer.

### Why do we bother if they are so noisy and slow

Because quantum computers are good at executing multiple instructions. And since algorithms can achieve exponential speedup, this can overcome the slow computer implementation.

Quantum computers for small problem size, are way worse than classical computers, so break-even point is late.
So we are interested in problems which classical computing wouldn't even do (month of computational time).

Need to have a problem that is not solvable classically in reasonable amount of time. But also problem solution has to be worth expensive running cost of quantum computer.

For example: breaking cryptography of AES. Even on optimistic quantum computer, we do **resource estimation** by performing compilation for a hypothetical quantum machine, we see that it's going to take 10,000 years.

Quadratic speedup now is not enough, cubic could be enough, and exponential speedup is more real.

But now quantum algorithms are not that widespread - only some factoring problems for breaking crypto, simulating chemistry, etc.

And normally you don't run the program twice, as it is only one solution. This gives different perspective if it is worth to write a program for quantum computer.

### Getting data into quantum computer is slow

Quantum computers are not good at solving big data problems (e.g. ML). They are better are big compute problems.

The data that quantum computer computes, e.g. for chemistry, can be used as input to train ML models on classical computer.

## Different layers of abstraction

Going bottom up: physical layer and then Mathematical model.

### Bottom

QPU does something physical (physical world)

### First layer: **Physical ISA**

Operation that we use to control the QPU: quantum operations on 1 or 2 qubits.

**Qubit** has a quantum state. $\Ket{\Phi} = (a0, a1)$ where $a_0, a_1 \in \Complex$ such that $|a_0|^{2} + |a_1|^{2} = 1$ (where probabilities add up to 1).
E.g. $\Ket{0}$ state = (1 0), $\Ket{1}>$ state = (0 1), |+> state = (1/sqrt(2) 1/sqrt(2)), |-> state = (1/sqrt(2) -1/sqrt(2))

This is the main difference, as plus and minus states are different amplitudes, even though probabilities are the same. Amplitudes affect computation.

For the quantum computing state (0 1) = -(0 1). (scalar product that still equation equals to 1). $|\Phi\angle \text{and} e^{i\Theta}|\Phi\angle$ are equal up to global phase

Each qubit has a state, and when measured we get random output with probabilities of the state. Usually we measure when we know that the state will be in some high probability.

**Quantum operation** on 1 qubit is 2x2 unitary matrix in complex numbers.
$U \in \Complex^{2x2} \text{ is unitary if } U^{+}U = UU^{+} = I$ where $U^{+} = (U^{*})^{T}$

|0> and |1> are eigen vectors of Z
|+> and |-> are eigen vectors of X

Pauli matrices:

$$
X = \begin{matrix}
    0 && 1 \\
    1 && 0
\end{matrix}
$$

$$
Z = \begin{matrix}
    1 && 0 \\
    0 && -1
\end{matrix}
$$

$$
Y = \begin{matrix}
    0 && -i \\
    i && 0
\end{matrix} = iXZ
$$

Hadamad operation $$H = \frac{1}{\sqrt{2}}\begin{matrix}
    1 && 1 \\
    1 && -1
\end{matrix}$$

Applying Hadamad: H |0> = |+>, H |+> = |0>, H |1> = |->, H |-> = |1>

$$
S = \begin{matrix}
    1 && 0 \\
    0 && i
\end{matrix} \text{where} S^2 = Z
$$

$$
S\begin{matrix}
    a_0 \\
    a_1
\end{matrix} = \begin{matrix}
    a_0 \\
    i a_1
\end{matrix}
$$

We can multiply these operations: e.g. H \* X \* H = Z

If we multiply all operations together, we get a powerset of ~24. Clifford operations: I X Y Z H S.

We want computational expressiveness of quantum operations have universal computation. (we want to find quantum `nand` gate)

We pick a gate that is not expressed by Clifford gates:

$$
T = \begin{matrix}
    1 && 0 \\
    1 && e^{i\pi/4}
\end{matrix}  \text{ s.t. } T^{2} = S
$$

Clifford + T + Cnot is universal set:

Forall U (2x2 unitary matrix), and Forall epsilon > 0, there Exists G1, ... Gk in Clifford+T, such that U' = G1 \* G2 \* ... \* Gk defines ||U - U'|| < epsilon
