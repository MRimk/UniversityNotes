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
