# DAA Lab-6 – Question 2

## Problem Statement

Implement the 0/1 Knapsack problem using Dynamic Programming.

Given N items with their weights and profits and a knapsack of
capacity W, determine the maximum profit that can be obtained.

## Approach

A 2D DP table is used.

dp[i][w] represents the maximum profit obtainable using the first
i items with a knapsack capacity of w.

For every item, there are two choices:

1. Include the item.
2. Exclude the item.

The better of the two choices is selected.

## Input

1. Number of items N
2. Knapsack capacity W
3. Weight of each item
4. Profit of each item

## Output

Maximum profit that can be obtained.

## Algorithm

1. Read N and W.
2. Read the weights and profits.
3. Create a DP table.
4. For each item and capacity:
   - If the item fits, choose the maximum of including and
     excluding the item.
   - Otherwise, exclude the item.
5. Display dp[N][W].

## Complexity Analysis

Time Complexity: O(N × W)

Space Complexity: O(N × W)

## Compilation

```bash
gcc q2_knapsack.c -o q2
```
