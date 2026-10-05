# Rod Cutting with Reconstruction

## Problem Statement

Given a rod of length `n` and an array of prices where `price[i]` represents the price of a piece of length `i`, determine:

1. The maximum revenue obtainable.
2. The exact piece lengths used to obtain the maximum revenue.

The total length of all pieces must be exactly `n`.

## Approach

Dynamic Programming is used.

Define:

```text
dp[i] = maximum revenue obtainable from a rod of length i
```

For every possible first cut:

```text
dp[i] = max(
    price[j] + dp[i-j]
)
```

An additional array `cut[]` is maintained to remember the first cut that produces the optimal revenue.

This allows the actual decomposition to be reconstructed.

## Input

The program takes:

1. Rod length `n`
2. Prices for pieces of lengths `1` through `n`

## Output

The program prints:

- Maximum revenue
- Lengths of the pieces in the optimal decomposition

## Example

### Input

```text
Enter rod length: 8
Enter prices for pieces of length 1 to 8:
1 5 8 9 10 17 17 20
```

### Output

```text
Maximum Revenue = 22
Optimal pieces: 2 6
```

The revenue is:

```text
price[2] + price[6]
= 5 + 17
= 22
```

## Algorithm

1. Read rod length `n`.
2. Read prices `price[1...n]`.
3. Initialize `dp[0] = 0`.
4. For each rod length:
   - Consider every possible first cut.
   - Calculate the revenue.
   - Store the maximum revenue.
5. Store the cut that gives the maximum revenue.
6. Starting from `n`, repeatedly use `cut[n]` to reconstruct the pieces.
7. Print the maximum revenue and piece lengths.

## Complexity Analysis

- Time Complexity: **O(n²)**
- Space Complexity: **O(n)**

## Concepts Used

- Dynamic Programming
- Rod Cutting
- Optimization
- Reconstruction
- Bottom-Up DP

## File

```text
q7_rod_cutting.c
```
