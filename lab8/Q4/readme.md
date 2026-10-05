# Longest Increasing Subsequence (LIS)

## Problem Statement

Given an integer array, find the length of the longest subsequence such that all elements are strictly increasing.

For example:

```text
10 22 9 33 21 50 41 60
```

One longest increasing subsequence is:

```text
10 22 33 50 60
```

Therefore, its length is `5`.

## Approach

Dynamic Programming is used.

Define:

```text
dp[i] = length of the longest increasing subsequence
        ending at index i
```

Initially:

```text
dp[i] = 1
```

because every individual element forms an increasing subsequence of length `1`.

For every pair `j < i`, if:

```text
arr[j] < arr[i]
```

then:

```text
dp[i] = max(dp[i], dp[j] + 1)
```

## Input

The program takes:

1. Number of elements `n`
2. Array elements

## Output

The length of the Longest Increasing Subsequence.

## Example

### Input

```text
Enter number of elements: 8
Enter array elements:
10 22 9 33 21 50 41 60
```

### Output

```text
Length of Longest Increasing Subsequence = 5
```

## Algorithm

1. Read `n`.
2. Read the array.
3. Create a DP array of size `n`.
4. Initialize every `dp[i]` to `1`.
5. For each index `i`:
   - Check all previous indices `j`.
   - If `arr[j] < arr[i]`, update `dp[i]`.
6. Find the maximum value in `dp`.
7. Print the result.

## Complexity Analysis

- Time Complexity: **O(n²)**
- Space Complexity: **O(n)**

## Concepts Used

- Dynamic Programming
- Subsequence
- Array Processing
- Optimization

## File

```text
q4_lis.c
```
