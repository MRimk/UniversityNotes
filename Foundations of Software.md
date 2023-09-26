<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

# Foundations of Software

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

The **multi-step evaluation** relation $\rightarrow*$ is the reflexve, transitive closure of single-step evaluation.

