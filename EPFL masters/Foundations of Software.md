---
title: Foundations of Software
---

<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

## Models

### Induction

Principle of _complete induction_ on natural numbers. It states that if it holds for n, it holds for all numbers i where i < n.

An example of it is theorem: Every natural n > 1 is the product of (one or more) prime numbers.

_Proof_: By complete induction on n.
IH: Every natural 1 < m < n is the product of prime numbers.
If n is a prime number, then it is the product of itself.

Otherwise:

- By definition, there exist 1 < m1, m2 < n such that n = m1m2
- By the IH, m1 and m2 are both product of prime numbers
- Therefore, n = m1m2 is also a product of prime numbers.

This works because the implied begining is an empty set of natural numbers. And then we expand, so really we don't have a base case. If we want to have a base case, we get the empty set from n=2, because there are no numbers between 1 and 2.

Ordinary and complete induction is _interderivable_ -- assuming one, we can prove the other.

Complete induction can be done on other mathematical objects, e.g. integers and strings of characters, rationals, because they can be bijectively mapped to naturals. Reals cannot have complete induction, because there is not a finite number of decreasing steps to reach a base case.

### Syntax

Programs will be represented as trees of syntax.

N.B. Parenthesis don't matter.

Evaluation relation is a smallest step we can take to get from one configuration to another. Notation t1 --> t2.

## Structural induction on syntax

_Depth_ of a term t is the smallest i such that t is in $S_i$

From the defimition of $S$ it is clear that if a term $t$ is in $S_i$, then all of its immediate subterms must be in $S_{i-1}$, i.e. they must have strictly smaller depths.

This observation justifies the _principle of induction on terms_,

The set of constants appearing in a term t, written Consts(t), is defined as follows. It is a function because:

By structural induction on terms:
Base case true, false, 0 (because the IH are empty sets)
Case $succ\ t_1$. IH - $Const(t_1)$ has only one result.
Case $if\ t_1\ then\ t_2\ else\ t_3$: IH1 - $Const(t_1)$ has only one result, IH2 - $Const(t_2)$ has only one result, IH3 - $Const(t_3)$ has only one result.

Bad definition : BadConsts. Since it dose not have a definition for if case and it has 2 different definitions for 0, it is not well-founded and total.

**Theorem** The number of disting constants in a term is at most the size of the term. $|Consts(t)| \le size(t)$
**Proof**:
By structural induction on terms.
Case analysis on t:

1. Case true. $|\{true\}| \le 1$
2. Case $if\ t_1\ then\ t_2\ else\ t_3$.
   1. IH1 $|Consts(t_1)| \le size(t_1)$
   2. IH2 $|Consts(t_2)| \le size(t_2)$
   3. IH3 $|Consts(t_3)| \le size(t_3)$
   4. Prove $|Consts(t_1) \cup Consts(t_2) \cup Consts(t_3)| \le size(t_1) + size(t_2) + size(t_3) + 1$
   5. apply each IH once to conclude a simple algebra relation

### Abstract Machines

**Abstract machine** consists of a set of states and a transition relation on states, written $\rightarrow$

### Induction on Derivations

Side note:
Derivation tree means that the statement at the bottom is derivable.

Given an arbitrary derivation D with conclusion $t \rightarrow t'$ we assume the desired result for its immediate sub-derivation (if any) and proceed by a case analysis (using the previous lemma) of the final evaluation rule used in constructing the derivation tree.

Prove: If $t \rightarrow t'$, then $size(t') < size(t)$
Proof by induction on the derivation tree for $t \rightarrow t'$
Case analysis on evaluation rules.

1. Case E-If True.
   1. We know that $t = if\ true\ then\ t_2\ else\ t_3$, and $t' = t_2$
   2. $size(t_2) < size(true) + size(t_2) + size(t_3) + 1$ - which is always true since size is naturals and simplify $size(t_2)$ in both sides
2. Case E-If False.
   1. Same as above
3. Case E-If.
   1. We know that $t = if\ t_1\ then\ t_2\ else\ t_3$; $t_1 \rightarrow t_1'$; and $t' = if\ t_1'\ else\ t_2\ then\ t_3$
   2. IH: $size(t_1') < size(t_1)$
   3. algebraic simplification

The process is, since there exists a derivation tree for $t \rightarrow t'$, we can do a case analysis on the last rule in the derivation tree. And for each case we learn things for free and we can apply theses things each time to formulate induction hypotheses.

### Normal forms

**Normal form** - the term that cannot be evaluated any further. I.e. a term t is in normal form if and only if there is no t' such that $t \rightarrow t'$

Values should be in normal form, since it is the final result of the computation.

**Stuck term** is a term that is in normal form but is not a value (e.g. succ false)

Stuck terms model run-time errors.

### Multi-step evaluation

The **multi-step evaluation** relation $\rightarrow^*$ is the reflexve, transitive closure of single-step evaluation.

## Untyped Lambda calculus

Example where call-by-name does not evaluate to call-by-value in one step:
Call-by-value: $$(\lambda x.x)((\lambda y.y)(\lambda z.z)) \rightarrow^{value}(\lambda x.x)(\lambda z.z)$$

Call-by-name: $$(\lambda x.x)((\lambda y.y)(\lambda z.z)) \rightarrow^{name} (\lambda y.y)(\lambda z.z)$$

#### Termination of evaluation

**Theorem** - termination of evaluation - for every $t$ there is some normal form $t'$ such that $t \rightarrow^* t'$

This is not a Turing-complete then.

Lambda calculus does not terminate because of the $\Omega$ term.

#### Lambda calculus puzzles

Q: one-step evaluation of $t = (\lambda x.\ \lambda y.y\ x)(\lambda z.z)$
A: $t' = \lambda y.y\ (\lambda z.z)$
This showcases that $\lambda$ extends as far to the right as possible (in this case, as far as the parenthesis allow)

Q: one-step evaluation of $t = (\lambda x.\ \lambda y. x)(\lambda z. y\ z)$
A: $t' = \lambda y'. (\lambda z. y\ z)$

Q: one-step evaluation of $t = ((\lambda x.x) y)((\lambda z.z)(\lambda w.w))$
A: $t' = ((\lambda x.x) y)((\lambda z.z)(\lambda w.w))$
This is because y is not a value to apply E-APPABS rule, and we cannot reduce the right side because for E-APP2 because left side is not a value.
If it was **call-by-name**, then we could apply E-APPABS and E-APP1 to get $y((\lambda z.z)(\lambda w.w))$

#### Rules

**E-APP1** $t_1 \rightarrow t_1' \rArr t_1t_2 \rightarrow t_1' t_2$

**E-APP2** $t_2 \rightarrow t_2' \rArr v_1t_2 \rightarrow v_1 t_2'$

**E-APPABS** $(\lambda x. t_{12})v_2\rightarrow [x \rightarrowtail v_2] t_{12}$

### Recursion in Lambda calculus

Recursion and divergence are intertwined, so we need to consider divergent terms.

$$\Omega = (\lambda x.xx) (\lambda x. xx)$$

$\Omega$ evaluates in one step to itself. Therefore it never reaches a normal form - it _diverges_.

#### Iterated application

Suppose f is some $\lambda$-abstraction, and consider the following variant of omega:

$$Y_f = (\lambda x. f (x x))(\lambda x. f(xx))$$

This creates a "pattern of divergence":
$$Y_f = (\lambda x. f (x x))(\lambda x. f(xx)) \rightarrow f(\lambda x. f (x x))(\lambda x. f(xx)) \rightarrow f(f(\lambda x. f (x x))(\lambda x. f(xx))) ...$$
This is a problem because it never reaches anything, only diverges.

#### Delaying divergence

**poisonpill = $\lambda$y. omega**

**poisonpill** is a value. It delays the explosion of omega

**Delayed variant of omega**
omegav = $\lambda y. (\lambda x. (\lambda y. x x y))(\lambda x. (\lambda y. x x y))y$.

omegav is a normal form, however if we apply the argument v too many times, it diverges.

**Another variant**:

$z_f = \lambda y. (\lambda x. f(\lambda y. x x y))(\lambda x. f(\lambda y. x x y))y$

And if we apply $z_f$ to an argument v, we get this:

$$z_f\ v = (\lambda y. (\lambda x. f(\lambda y. x x y))(\lambda x. f(\lambda y. x x y))y)\ v \rightarrow (\lambda x. f(\lambda y. x x y))(\lambda x. f(\lambda y. x x y))v$$

$$\rightarrow f\ (\lambda y. (\lambda x. f(\lambda y. x x y))(\lambda x. f(\lambda y. x x y))y)\ v = f\ z_f\ v$$

Since $z_f$ and v are both values, the next computation step will be the reduction of f $z_f$

Example:
f = $\lambda fct.\ \lambda a.\ if\ n=0\ then\ 1\ else\ n\times\ (fct(pred\ n))$

$$z_f\ 3 \rightarrow^* f\ z_f\ 3 = (\lambda fct.\ \lambda n.\ ...) \rightarrow^* 3\times(z_f\ 2)...$$

**Define z = $\lambda f. z_f$**

READ: chapter 8.

#### Delaying evaluation in ite

We delay the evaluation of the branches of the if then else, we add an identity function afterwards to first evaluate the boolean evaluation. And we add dummy lamba wrappers for the branches
Test already has the unit. (sometimes)

#### Church numerals

There can be different representations of the same number which means that equality is under question.

If we enrich the pure lambda calculus with "regular numbers", we can display church numberal by converting them to regular numbers:
realnat = $\lambda$n. n ($\lambda$m. succ m) 0

### Inductive proofs about the lambda calculus

**Exercise**: If t -> t', then FV(t) $\supseteq$ FV(t').

**Proof**:
Proof by induction on the derivation tree of t -> t'.
Case analysis on the last rule used to derive t-> t'

Case E-App1:
from the case we get: t = t1 t2, t' = t1' t2, t1 -> t1', and IH: FV(t1) $\supseteq$ FV(t1')
FV(t1 t2) ?$\supseteq$ FV(t1' t2)
FV(t1 t2) = FV(t1) $\cup$ FV(t2)
FV(t1' t2) = FV(t1') $\cup$ FV(t2)
From IH and set theory: FV(t1) $\cup$ FV(t2) $\supseteq$ FV(t1') $\cup$ FV(t2)

Case E-App2:
Similar (use this in the exam)

Case E-AppAbs:
t = ($\lambda$x t12) v2, t' = [x -> v2]t12
FV(($\lambda$x t12) v2) ?$\supseteq$ FV([x -> v2]t12)
FV(($\lambda$x t12) v2) = FV($\lambda$x t12) $\cup$ FV(v2)
FV($\lambda$x t12 \\ {x}) $\cup$ FV(v2) ?$\supseteq$ FV([x -> v2]t12)

_Lemma 1_: FV([x -> t2]t1) $\subseteq$ FV($\lambda$x t1) \\ {x} $\cup$ FV(t2)
_Proof_:
By induction of the structure of t1.
Case t1 = x: FV([x -> t2]t1) ?$\subseteq$ FV(x) \\ {x} $\cup$ FV(t2)
FV(x) \\ {x} $\cup$ FV(t2) = {x} \\ {x} $\cup$ FV(t2)
FV([x -> t2]t1) = FV(t2)
Case t1 = y, y $\ne$ x:
Case t1 = t11 t12, y $\ne$ x:
Case t1 = ($\lambda$y t12), y $\notin$ FV(t2) (if y is in FV(t2), then we rename alpha rename ($\lambda$y t12)):
**exercise!!!!**

The most important theorem is that "if t is closed and t -> t', then t' is closed"

Understanding this:
If t is closed, then:
either t is a value
or $\exist$t', t -> t' - **progress**

If t -> t', and t is closed, then t' is closed - **preservation**

Progress + preservation = **safety/soundness**

### Progress

**Theorem:** If t is closed (FV(t) = {}), then t is a value or t -> t'
**Proof**:
Proof by induction on the structure of t
Case analysis on the structure of t

Case t = x: FV(t) = {x}, contradiction

Case t = $\lambda$x. t1 - it is a value

Case t = t1 t2:
FV(t) = FV(t1) $\cup$ FV(t2) = {} => therefore t1 and t2 are closed
By IH, t1 is a value or t1 -> t1'
By IH, t2 is a value or t2 -> t2'

If t1 -> t1', then E-App1 applies;
otherwise t1 is a value:
If t2 -> t2', then E-App2 applies;
otherwise t2 is a value, then
t = v1 v2, and v1 = $\lambda$x. t12,
then t= ($\lambda$x. t12) v2, which means E-AppAbs applies

test

## Skipped Typed Lambda Calculus

### Proof of preservation

Preservation: if {}/ |- t.T and t -> t', then {}/ |- t'.T

By induction on derivation of {}/ |- t.T

Case analysis of {}/ |- t.T

1 Case T-Var and T-Abs, cannot happen because t->/

2 Case T-App
t = t1t2
{}/ |- t1, T2 ->T
{}/ |- t2, T2
IH1: If t1 -> t1', {}/ |- t1.T2->T
IH1: If t2 -> t2', {}/ |- t2.T2

Subcase E-App1
t1 -> t1'
t' = t1't2
From IH1: {}/ |- t1'.T2 -> T
By T-App. {}/ |- ....

Subcase E-App2 - similar

Subcase E-AppAbs
t1 =\x.Tx.t12
t2 = v2
t' = [x -> v2]t12
To prove: {}/ |- [x -> v2]t12.T

case analysis of [x -> v2]t12

Case t12 = x
[x -> v2]t12 = v2
we need to prove that {}/ |- v2.T (from empty environment v2 has type T)

### Erasure

Takes the term from STLC, and takes it to the untyped lambda calculus

erase(x) = x
erase(\x:T1. t2) = \x. erase(t2)
erase(t1 t2) = erase(t1) erase(t2)

We need to have both true: first erase and then take a step in untyped lambda calculus or first take a step in STLC and then erase.

### The Curry-Howard Correspondence - comes up in the exam often

In constructive logics, a proof of P must provide evidence for P (law of excluded middle is not recognized - so $P \lor \neg P$ could be false)

A proof of $P \land Q$ is a _pair_ of evidence for P and evidence for Q.

A proof of $P \supset Q$ is a _procedure_ for transforming evidence for P into evidence for Q

Given the logic formula $(A \land B )\supset A$
Prove that it is true by giving a well-typed term of the approprate type.
\\(a\*b).a

Given the logic formula $((A \land B )\supset C) \supset (A \supset (B \supset C))$

| Logic                     | Programming languages              |
| ------------------------- | ---------------------------------- |
| propositions              | types                              |
| proposition $P \supset Q$ | type $P \rightarrow Q$             |
| proposition $P \land Q$   | type $P \times Q$                  |
| proof of proposition P    | term t of type P                   |
| proposition P is provable | type P is inhabited (by some term) |

## Extensions to STLC
