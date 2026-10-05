# Longest Common Subsequence (LCS)

## Problem Statement

Given two strings `X` and `Y`, find:

1. The length of their Longest Common Subsequence.
2. The actual LCS string.

A subsequence maintains the relative order of characters but does not necessarily contain consecutive characters.

## Approach

Dynamic Programming is used.

Define:

```text
dp[i][j]
```

as the length of the LCS of the first `i` characters of `X` and the first `j` characters of `Y`.

If the current characters are equal:

```text
X[i-1] == Y[j-1]
```

then:

```text
dp[i][j] = dp[i-1][j-1] + 1
```

Otherwise:

```text
dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

After constructing the DP table, traceback is performed to reconstruct the actual subsequence.

## Input

The program takes:

1. First string `X`
2. Second string `Y`

## Output

The program prints:

- Length of LCS
- Actual LCS

## Example

### Input

```text
Enter first string: ABCBDAB
Enter second string: BDCABA
```

### Output

```text
Length of LCS = 4
LCS = BCBA
```

Another LCS of the same length may also be possible.

## Algorithm

1. Read strings `X` and `Y`.
2. Let their lengths be `m` and `n`.
3. Create an `(m+1) × (n+1)` DP table.
4. Initialize the first row and column with `0`.
5. Compare characters of both strings.
6. If they match, take the diagonal value plus one.
7. Otherwise take the maximum of the upper and left values.
8. The final answer is `dp[m][n]`.
9. Perform traceback from `dp[m][n]`.
10. Construct and print the LCS.

## Complexity Analysis

- Time Complexity: **O(mn)**
- Space Complexity: **O(mn)**

## Concepts Used

- Dynamic Programming
- Two-Dimensional DP
- Sequence Comparison
- Traceback / Reconstruction

## File

```text
q3_lcs.c
```
