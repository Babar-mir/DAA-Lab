# DAA Lab-07 – Question 1

## Problem Statement

Invert an equilateral triangle of closely packed coins using the
minimum number of moves. In one move, one coin can be moved to a
new position.

## Approach

For a triangle containing n rows:

Total coins = n(n+1)/2

The minimum number of coin moves is:

floor(T / 3)

Therefore:

Minimum moves = floor(n(n+1) / 6)

## Input

Number of rows in the triangle.

## Output

- Total number of coins
- Minimum number of moves

## Complexity Analysis

Time Complexity: O(1)

Space Complexity: O(1)

## Compilation

```bash
gcc q1_coin_triangle.c -o q1
```
