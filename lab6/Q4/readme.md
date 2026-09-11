# DAA Lab-6 – Question 4

## Problem Statement

Implement Matrix Chain Multiplication using Dynamic Programming.

Given the dimensions of N-1 matrices in an array arr[], determine
the minimum number of scalar multiplications required to multiply
the complete matrix chain.

## Approach

A 2D DP table is used.

dp[i][j] stores the minimum number of scalar multiplications
required to multiply matrices i through j.

Every possible position for splitting the matrix chain is checked,
and the minimum cost is stored.

## Input

1. Number of dimensions N
2. N dimensions in the array arr[]

For example:

N = 4

arr = {10, 30, 5, 60}

represents:

A1 = 10 × 30
A2 = 30 × 5
A3 = 5 × 60

## Output

Minimum number of scalar multiplications required.

## Algorithm

1. Read N and the dimension array.
2. Initialize dp[i][i] = 0.
3. Consider chains of increasing length.
4. For every chain, try every possible split point k.
5. Calculate:

   dp[i][k] + dp[k+1][j]
   - arr[i-1] _ arr[k] _ arr[j]

6. Store the minimum cost.
7. Display dp[1][N-1].

## Complexity Analysis

Time Complexity: O(N^3)

Space Complexity: O(N^2)

## Example

Input:

N = 4

arr = {10, 30, 5, 60}

Output:

4500

## Compilation

```bash
gcc q4_matrix_chain.c -o q4
```
