<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029 MD007-->

# Compiler Construction

## Lecture 1

There are compilers that translate one language to another (C to assembly), language to bytecode (Java to JVM bytecode), language to itself (C to C, to make it faster, or smaller or smt else)

Uses of compiler technology:

1. Translate a program in a highlevel language to machine code
2. Optimization
3. Text formatters (TeX to dvi)
4. Interpreters (on-the-fly translation)
5. Automatic parallelization or vectorization
6. Performance instrumentation
7. Security (e.g. Address Sanitizer)
8. etc

Key point: extract properties of a program and transform it (analysis and synthesis)

Possible optimizations:

- if a variable is not used, _eliminate dead code_
- if a variable is not reassigned, move it out of the loop, i.e. do _loop invariant code motion_
- if a loop variable is not used much, substitute it by the one that is used, i.e. _induction variable substitution_
- if two expressions have the same part (e.g. x \* y), assign it to a separate var, i.e. _common subexpression elimination_

Compiler typically produces machine code (processes source codew, and produces target machine specific target code; result - fast execution)

Intepreter executes source code (generates intermediate representation, software interpretation of the code, result - slow execution)

Compiler stages:

1. Front-end for analysis (transform a string to what can be understood)
2. Semantic representation and processing
3. Back-end for synthesis

If the analysis and synthesis are separated, there has to be L \* M compilers

Intermediate code can be abstract syntax tree (AST) which is constructed from the grammar.

### Parser's purpose

To produce AST:

1. Lexical analysis ('a' -> Letter)
2. Syntax analysis
3. Context handling (we will ignore it)

To have a parser, usually use Recursive Descent Parsing. This uses one procedure per construct, and descends deeper.
First Scanner turns input string to a list of tokens and then parser converts this list to the tree-like structure to represent how tokens fit together and interact with each other.

First parser gets the next token and parses a single expression.
When getting the next token, assign the type and value to the created token.

### Backend part

To create simple machine code, have a recursive switch statement, which traverses the AST.

To interpret, it is the same process, except when in the switch cases, don't create code, but execute instructions of the expressions.

## Lecture 2

### Languages

Alphabeth Sigma (that can be characters, digits, operators)
Sigma \* is a set of finite sequences
And thus language L is a subset of Sigma \*

**Context-free grammars** describe how languages are being formed. There are rules to generate the language. And these rules consist of productions (head -> body). These elements are derivations - made by substituting head by body. There can be terminal or non-terminal symbols. However, if it is context-free grammar - head is a single non-terminal symbol.

**Language** consists of:

- sentinel forms (intermediate strings that are derived from the initial string)
- sentences (sentinel forms that only consist of terminal symbols (final sentinel form))
- L(G) (language that grammar produces) is a set of all sentences that we can derive from the start S via productions

**Notation**:\
instead of A -> aBc and A -> D can be A -> aBc | D

**Properties** of context-free grammar:

- it is left recursive if A -> A x
- it is right recursive if A -> x A
- grammar is ambiguous if there are several derivations for the same sentence

**Recognizer**: given sentence S and grammar G, recognizer will return "yes" if s c L(G), and "no" if it is not

**Lexer** removes whitespace or comments and transforms the string into a sequence of tokens

**Parser** decides if tokens are in the language by building the derivation

### Lexer

token: < name, value >
pattern: describes how the token looks.
lexeme: string that matches the pattern

Example: pos = init + r \* 60 => < id, pos > < = > < id, init > < + > < id, r > < \* > < 60 >

### Parser

Goal: translate tokens to AST

Example:

```C
while(a != 0){
    printf("%d",a);
    a = a - 1;
}
```

AST:

- while
  - !=
    - var a
    - const 0
  - block
    - call
      - printf...

Steps:

1. Given a CFG for the language
2. for some string s construct a derivation of s
3. from derivation construct AST

Example:
s -> e + s | e
e -> number | (s)
Derive (1 + 2 + (3 + 4)) + 5

s -> e + s -> (s) + s -> (e + s) + s -> (1 + s) + 5 -> (1 + e + s) + 5 -> (1 + 2 + (s)) + 5 -> (1 + 2 + (e + s)) + 5 -> (1 + 2 + (3 + 4)) + 5

What is a derivation:

1. start from s
2. apply productions until we get sentence
3. For arbitrary alpha, beta, gamma and production A -> beta, a single derivation step subtitutes _alpha A gamma_ with _alpha beta gamma_

### Parse tree

- leaves are terminals
- inner nodes are non-terminals
- no information about the derivation order

Rules:

- Grammar G = (N, Sigma, P, S)
- root labeled with S
- leaf is labeled with a c Sigma
- interior nodes are labeld with a c N
- if interior node is labeled with A and children Beta1, ..., Betan then (A -> Beta1 ... Betan) is a production
- string formed by leaves is called yield

### Parse tree vs AST

Parse tree is concrete syntax tree, whereas AST is abstract syntax tree

Compute AST by deleting information from parse tree

### Derivation order

for production A -> B, replace alpha A gamma by alpha beta gamma

there are different orders:
leftmost, rightmost

Usually the parse tree will be the same if grammar is not ambiguous.

A grammar G is **ambiguous** if for some s c L(G), there are two diffrent parse-trees.

Eliminating ambiguity:
disambiguate by adding more non terminals

Example: 1 + 2 \* 3
it was: s -> s + s | s \* s | number

Now:
s -> s + t | t
t -> t \* num | num

Example of ambiguous grammar:
S -> if(E) S
S -> if(E) S else S

statement: if(E1) if(E2) S1 else S2, we don't know to which if we have to match.

unambiguated:

- split into matched and unmatched statement: S -> matched | unmatched
- and no unmatched grammar between if ... else

### Questions

Grammar G:
A -> (B) | !
B -> A | AB | empty

_Q1_: _is G ambiguous?_
Yes, because there can be two different parse trees. Argument: (()).
Derivation 1: A -> (B) -> (A) -> ((B)) -> (())
Derivation 2: A -> (B) -> (AB) -> ((B)B) -> (()B) -> (())
If there are transitions that give choice (in this case B -> A or B -> AB (where B is empty)), it leads to ambiguity.

_Q2_: _Why are ambiguous grammars bad?_
If the grammar is ambiguous, and it might change the order of execution from what is intended. And because the parsers become non-deterministic

_Q3_: _What happens, if we use a recursive descent parser in G?_
Because the grammar is ambiguous, it will pick the first match (A), thus does not cover the other case (AB). But if the grammar is commuted B -> AB | A | empty

_Q4_: _What are First(A), First(B), Follow(A), Follow(B)?_
First(A) = {!, (}
First(B) = {!, (, empty}
Follow(A) = {EOF, !, (, empty, )}
Follow(B) = {EOF, !, (, )}

_Q5_: _What are these sets good for?_
First(A) is a set of elements that A is responsible in the string.
In the LL(1), it looks ahead to see what is each derivation responsible for in the string.

_Q6_: _Is G in LL(1)?_
LL(1) means that there is a top-down symbol and the leftmost symbol will be expanded first, and there is only **1** lookahead.

## Lecture 3

## Lecture 5

### LLVM IR

LLVM combines low-level control (like assembly) and high-level information such as types.

_Q_: _How is LLVM different/similar to assembly?_
Assembly does not have static single assignment, unlimited registers.
Low-level aspects: it depends on the assembly. If assembly is RISC ISA, then there is RISC-like address codes; simple, low-level control flow structs.

_Q_: _How is LLVM different/similar to C?_
Types, etc.

_Q_: _what is the difference between a LLVM register and a LLVM "variable"?_
All registers are understood as variables, thus typically they are the same, but sometimes there it was meant to be global variable, instead of just a variable.

_Q_: _can compilation on different targets result in different LLVM IR outputs?_
LLVM IR is, in theory, target independent, so no. This can be interpreted that the syntax is language and target independent.
However, target-specific optimization can still be in the middle-end, since it is sometimes easier to do that rather than doing it in the backend. Target-dependent libraries or inline code (as in if x86 arch do this, if ARM do this) also means that there can be different resulting outputs. Inline assembly can affect the resulting code. The frontend could do target-specific things, such as integers can be unspecified length, and if the system, for example, is not 64bit i64 could not be used.

_Q_: _how are arrays and structs different than C?_
Explicit 0 initializer in global variables.
Pointers and arrays in LLVM are different things, because LLVM cares about explicit types. And array in LLVM is not an integer, thus not a pointer.
Structs are similar to C, but field names are not preserved.
If a C union is complied with LLVM IR, then frontend would need to specifically cast each time, the union part if accessed.

Module in LLVM:
it depends. (C module is like a file with .c or a header file).
However, in LLVM at compile time module is the individual C files, and in LLVM link time module takes the necessary modules and make a single module that is made out of those, thus representing the whole program.

_Q_: _How many times a typical GEP instruction access memory?_
it does not. (getelementptr is doing type element-aware pointer arithmetic)

## Optimizations

Most optimizations are at IR level, but some can be in the frontend.

Regular LLVM does not have High and Low IR for now.

Optimization - code transformation where space and/or time are improved.

Code optimizations must be safe - they preserve the meaning of the program, and must be left unoptimized if cannot prove correctness.

Ultimate goal - optimize program hot spots, which is mostly loops, functions, etc.

_Q_ _how does inlining work in presence of recursion? And in presence of indirect calls?_
If the depth is known then it can be unwrapped, but usually just give up. For the indirect calls, if the function pointer is constant, ie we can know that the pointer points to a function, then we can do inlining. It is possible to have indirect call that does indirect call promotion, such that indirect call is translated to multiple direct calls, where it can jump to correct inlined code according to the pointer value.

Function cloning - function can be cloned and a special edition is created for the use.

_Q_ - _Cloning and inlining similarities/differences?_
Similarities: duplicating code and specializing the code sides, such that later those parts are optimized.
Difference: with cloning the call is still there, with cloning the code can increase more than inlining (but it can be otherwise still; usually cloning produces smaller code than inlining only because we clone iff it is known that there is advantage for the optimization).

_Q_ _what optimization passes are needed to optimize the following code away (assume x and y are dead at the end of the snippet)?_

```C
int x = INT_MAX - 1;
int y = x;
if (y < 0)
  printf("Oops!")
```

1. Constant folding - calculate INT_MAX - 1
2. Constant propagation on x => y = INT_MAX - 1
3. Constant propagation on y (to if condition)
4. Arithmetic simplication into false (INT_MAX - 1 is not < 0)
5. Unreachable code elim (inside of if)
6. Dead code elimination (x and y are dead)

**Loop-invariant code elimination** - if the result of statement/expression does not change during the loop and there are no externally visible side effects, it can be moved out of the loop

**Induction variable elimination** - eliminate other variable to leave just one induction variable that is used

**Loop unrolling** - execute loop body multiple times at each iteration. It faces the same problem like inlining, since what is the limit of how many lines is good amount of lines.

_Q: which of the loop optimizations considered can benefit from a profile-guided optimization strategy?_
After getting the profiling, there is a profile-guided strategy.
Loop-invariant code motion benefits if the fast-path (indirect code promotion) and then uses the invariant code, otherwise does not use invariant code.
Induction Variable Elimination - we just use speculative optimizations, ie if therer is some uncertainty that cannot be resolved by static analysis, based on speculation, there can be a decision made.
Loop unrolling - profiling helps to get a better estimation of the unrolling cost. Find the amount of times the loop runs (trip count), and find the optimal number that can be unrolled. Find if there are other loops elsewhere in the code, ie find whether it is a hotspot or not (thus if it needs to be bloated or not).

Statically trip count can be found if it is constant, constant variable, or after the constant propagation, or there is an invariant. When the exact value is known, the loop can be removed and the loop body is copy pasted. However, this is dependant if the trip count is not too big.

Liveness idea: we want to know what is dead in the future such that we do not have it now.

_Q it takes many scanse to reach convergence with oir fixed-point algorithm, can we make the infividual scans more efficient?_
Skip applying formulas for every point.

### Copy propagation

Goal - determine copies available at each program point

_Q why is the pre-order used for the fixed point analysis rather than post-order like in liveness?_
Here the order does not matter since convergence is not affected and is still correct, but speed is affected. This is different to the liveness analysis, where order is important since we are looking into the future if it is used

### Data-flow analysis

Structured framework to have these analysis passes. They would have transfer functuons, where forward and backward analysis is transfered to/from in/out.

_Q Can we replace PHI Nodes with Select instructions?_
We can insert additional information in the blocks to say from which block we came from. We can cheat SSA by passing register SSA by storing information in memory and then loading the var.
Assuming we don't want to cheat SSA with memory. We can do that by extracting the variable from the condition and assigning the value of select. This is what happens in LLVM compiler where if assignments get flattened to selects.
However, this replacement can work for simple if statements, for example, in the for loops, which we cannot unwrap, we have to use the PHI nodes.

## LLVM Passes

Hierarchy: Module -> Functions -> BasicBlocks -> Intructions

Types of passes: (we get more points if we pick correct pass - most restrictive that works)

1. ModulePass - least restrictive pass
2. FunctionPass - cannot create or remove functions
3. LoopPass - calls pass for every loop
