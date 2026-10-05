# Maximum Sum Increasing Subsequence

## Problem Statement

Given an array of positive integers, find the maximum possible sum of a strictly increasing subsequence.

Unlike LIS, this problem maximizes the **sum of elements**, not the length.

## Approach

Dynamic Programming is used.

Define:

```text
dp[i] = maximum sum of an increasing subsequence
        ending at index i
```

Initially:

```text
dp[i] = arr[i]
```

For every previous index `j`:

```text
j < i
```

if:

```text
arr[j] < arr[i]
```

then:

```text
dp[i] = max(dp[i], dp[j] + arr[i])
```

The maximum value in `dp` is the answer.

## Input

The program takes:

1. Number of elements `n`
2. Array elements

## Output

The maximum sum of a strictly increasing subsequence.

## Example

### Input

```text
Enter number of elements: 7
Enter array elements:
1 101 2 3 100 4 5
```

### Output

```text
Maximum Sum Increasing Subsequence = 106
```

One optimal subsequence is:

```text
1 2 3 100
```

Sum:

```text
1 + 2 + 3 + 100 = 106
```

## Algorithm

1. Read `n`.
2. Read the array.
3. Create a DP array.
4. Set `dp[i] = arr[i]`.
5. For every element:
   - Check all previous elements.
   - If the previous element is smaller, update the sum.
6. Find the maximum value in `dp`.
7. Print the maximum sum.

## Complexity Analysis

- Time Complexity: **O(n²)**
- Space Complexity: **O(n)**

## Concepts Used

- Dynamic Programming
- Increasing Subsequence
- Maximum Sum
- Bottom-Up DP

## File

```text
q5_max_sum_increasing_subsequence.c
```
