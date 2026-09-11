---

# README.md — Q4

````markdown
# DAA Lab-06 – Question 4

## Problem Statement

Given a permutation of integers 1 to n, sort it using only
reversal operations.

The cost of reverse(p, i, j) is the number of elements in the
reversed range.

## Approach

A divide-and-conquer merge sort is used.

The two sorted halves are merged using rotations implemented
through three reversals.

For:

[A][B]

the rotation:

[B][A]

is performed using:

1. reverse(A)
2. reverse(B)
3. reverse(A+B)

## Proof

At most O(n) reversals are sufficient to sort any permutation
because each element can be placed into its correct position
using at most one reversal.

For the cost-based algorithm:

Merge cost = O(n log n)

The complete recurrence is:

T(n) = 2T(n/2) + O(n log n)

Therefore:

T(n) = O(n log² n)

## Input

- Number of elements n
- A permutation of 1 to n

## Output

Sorted permutation.

## Compilation

```bash
gcc q4_reversal_sort.c -o q4
```
````
