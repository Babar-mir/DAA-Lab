# DAA Lab-07 – Question 7

## Problem Statement

Implement Matrix Chain Multiplication using Dynamic Programming.

Find:

1. Minimum number of scalar multiplications.
2. Optimal ordering of matrix multiplication.

## Approach

dp[i][j] stores the minimum number of scalar multiplications
required to multiply matrices Ai through Aj.

A split point k is tested for every possible matrix chain.

The split position is stored in split[i][j] to reconstruct the
optimal parenthesization.

## Input

Number of dimensions N.

N dimensions of the matrices.

For example:

10 30 5 60

represents:

A1 = 10 × 30
A2 = 30 × 5
A3 = 5 × 60

## Output

- Minimum scalar multiplications
- Optimal matrix multiplication ordering

## Example

Input:

4
10 30 5 60

Output:

Minimum number of scalar multiplications = 4500

Optimal ordering = ((A1A2)A3)

## Complexity Analysis

Time Complexity: O(N³)

Space Complexity: O(N²)

## Compilation

```bash
gcc q7_matrix_chain.c -o q7
```
