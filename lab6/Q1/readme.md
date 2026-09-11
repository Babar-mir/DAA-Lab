# DAA Lab-6 – Question 1

## Problem Statement

Find the nth Fibonacci number using Dynamic Programming.

## Approach

The Fibonacci sequence is calculated using a DP array.

The previous two calculated values are used to calculate the
next Fibonacci number.

## Input

The value of n.

## Output

The nth Fibonacci number.

## Algorithm

1. Read n.
2. Initialize dp[0] = 0 and dp[1] = 1.
3. For i = 2 to n:
   dp[i] = dp[i-1] + dp[i-2]
4. Display dp[n].

## Complexity Analysis

Time Complexity: O(N)

Space Complexity: O(N)

## Compilation

```bash
gcc q1_fibonacci.c -o q1
```
