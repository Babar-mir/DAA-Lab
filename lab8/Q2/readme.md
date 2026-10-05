# Coin Change — Total Number of Ways

## Problem Statement

Given an array of distinct positive integer coin denominations and a target amount `V`, find the total number of distinct combinations that produce the target amount.

An unlimited number of coins of every denomination is available.

The order of coins does not matter.

For example:

```text
1 + 2
```

and

```text
2 + 1
```

are considered the same combination.

## Approach

Dynamic Programming is used.

Define:

```text
dp[i] = number of ways to make amount i
```

Initialize:

```text
dp[0] = 1
```

For every coin, update all amounts from the value of the coin up to `V`.

```text
dp[amount] += dp[amount - coin]
```

Processing coins one by one ensures that different orders are not counted separately.

## Input

The program takes:

1. Number of coin denominations
2. Coin denominations
3. Target amount `V`

## Output

The total number of distinct combinations that produce `V`.

## Example

### Input

```text
Enter number of coin denominations: 3
Enter coin denominations:
1 2 5
Enter target amount: 5
```

### Output

```text
Total number of ways = 4
```

The combinations are:

```text
5
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1
```

## Algorithm

1. Read the number of denominations.
2. Read all coin denominations.
3. Read target amount `V`.
4. Create `dp[0...V]`.
5. Initialize `dp[0] = 1`.
6. For every coin:
   - Iterate from the coin value to `V`.
   - Update `dp[amount]`.
7. Print `dp[V]`.

## Complexity Analysis

- Time Complexity: **O(nV)**
- Space Complexity: **O(V)**

## Concepts Used

- Dynamic Programming
- Unbounded Coin Change
- Counting Combinations
- Bottom-Up DP

## File

```text
q2_coin_change_ways.c
```
