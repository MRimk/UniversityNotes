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

_Q1_: is G ambiguous?
Yes, because there can be two different parse trees. Argument: (()).
Derivation 1: A -> (B) -> (A) -> ((B)) -> (())
Derivation 2: A -> (B) -> (AB) -> ((B)B) -> (()B) -> (())
If there are transitions that give choice (in this case B -> A or B -> AB (where B is empty)), it leads to ambiguity.

_Q2_: Why are ambiguous grammars bad?
If the grammar is ambiguous, and it might change the order of execution from what is intended. And because the parsers become non-deterministic

_Q3_: What happens, if we use a recursive descent parser in G?
Because the grammar is ambiguous, it will pick the first match (A), thus does not cover the other case (AB). But if the grammar is commuted B -> AB | A | empty

_Q4_: What are First(A), First(B), Follow(A), Follow(B)?
First(A) = {!, (}
First(B) = {!, (, empty}
Follow(A) = {EOF, !, (, empty, )}
Follow(B) = {EOF, !, (, )}

_Q5_: What are these sets good for?
First(A) is a set of elements that A is responsible in the string.
In the LL(1), it looks ahead to see what is each derivation responsible for in the string.

_Q6_: Is G in LL(1)?
LL(1) means that there is a top-down symbol and the leftmost symbol will be expanded first, and there is only **1** lookahead.
