# DAA Lab-07 – Question 5

## Problem Statement

A target can hide in n positions arranged along a straight line.
The target moves to an adjacent position between every two
consecutive shots.

The shooter cannot see the target and must design a strategy that
guarantees hitting it.

## Approach

For n >= 4, use the following sequence:

2, 3, ..., n-1, n-1, ..., 3, 2

The shooter first sweeps from left to right and then sweeps
backwards.

Special cases:

n = 2: 1, 1

n = 3: 2, 2

## Input

Number of hiding spots n.

## Output

- Shooting sequence
- Whether the target is guaranteed to be hit
- Number of shots

## Complexity Analysis

The strategy requires O(n) shots.

The validation program maintains all possible target positions,
requiring:

Time Complexity: O(n²)

Space Complexity: O(n)

## Compilation

```bash
gcc q5_moving_target.c -o q5
```
