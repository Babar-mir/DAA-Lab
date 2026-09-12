# DAA Lab-07 – Question 2

## Problem Statement

Given E identical eggs and F floors, determine the minimum number
of egg droppings required to determine the highest floor from which
an egg can fall without breaking.

## Approach

Dynamic Programming is used.

dp[e][f] represents the minimum number of trials required using
e eggs and f floors.

For every possible dropping floor x:

dp[e][f] =
1 + min(max(dp[e-1][x-1], dp[e][f-x]))

## Input

- Number of eggs E
- Number of floors F

## Output

Minimum number of droppings required.

## Example

Input:

E = 2
F = 100

Output:

14

## Complexity Analysis

Time Complexity: O(E × F²)

Space Complexity: O(E × F)

## Compilation

```bash
gcc q2_egg_dropping.c -o q2
```
