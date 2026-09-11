# DAA Lab-6 – Question 3

## Problem Statement

Implement the Longest Common Subsequence (LCS) algorithm using
Dynamic Programming.

Given two strings, find the length of their longest common
subsequence and display the subsequence.

## Approach

A 2D DP table is constructed.

dp[i][j] represents the length of the LCS of the first i characters
of the first string and the first j characters of the second string.

After calculating the table, it is traversed backwards to
reconstruct the actual LCS.

## Input

Two strings.

## Output

1. Length of the LCS
2. The LCS itself

## Algorithm

1. Read two strings.
2. Create a DP table.
3. If the current characters are equal:
   dp[i][j] = dp[i-1][j-1] + 1
4. Otherwise:
   dp[i][j] = max(dp[i-1][j], dp[i][j-1])
5. The value dp[m][n] gives the LCS length.
6. Traverse the table backwards to reconstruct the LCS.
7. Display the length and subsequence.

## Complexity Analysis

Time Complexity: O(M × N)

Space Complexity: O(M × N)

where M and N are the lengths of the two strings.

## Compilation

```bash
gcc q3_lcs.c -o q3
```
