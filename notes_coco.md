<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

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

### Parser

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
