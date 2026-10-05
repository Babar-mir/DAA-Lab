# Minimum Coin Change

## Problem Statement

Given an array of coin denominations and a target amount `V`, find the minimum number of coins required to make the target amount.

An unlimited number of coins of each denomination is available. If the target amount cannot be formed using the given denominations, return `-1`.

## Approach

Dynamic Programming is used.

Define:

```text
dp[i] = minimum number of coins required to make amount i
```

Initialize:

```text
dp[0] = 0
```

For every amount from `1` to `V`, try every available coin.

If:

```text
coin <= amount
```

then:

```text
dp[amount] = min(dp[amount],
                  dp[amount - coin] + 1)
```

If `dp[V]` remains infinity, the target cannot be formed.

## Input

The program takes:

1. Number of coin denominations
2. Coin denominations
3. Target amount `V`

## Output

The program prints the minimum number of coins required.

If the target cannot be formed, it prints `-1`.

## Example

### Input

```text
Enter number of coin denominations: 3
Enter coin denominations:
1 5 6
Enter target amount: 11
```

### Output

```text
Minimum number of coins = 2
```

The target is formed as:

```text
5 + 6 = 11
```

## Algorithm

1. Read `n`, the number of coin denominations.
2. Read the coin denominations.
3. Read target amount `V`.
4. Create a DP array of size `V + 1`.
5. Set `dp[0] = 0`.
6. Initialize all other values to infinity.
7. For every amount from `1` to `V`:
   - Check every coin.
   - If the coin can be used, update the minimum.
8. If `dp[V]` is infinity, print `-1`.
9. Otherwise, print `dp[V]`.

## Complexity Analysis

- Time Complexity: **O(nV)**
- Space Complexity: **O(V)**

## Concepts Used

- Dynamic Programming
- Bottom-Up DP
- Arrays
- Minimum optimization

## File

```text
q1_minimum_coin_change.c
```
