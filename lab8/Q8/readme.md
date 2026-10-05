# Optimal Binary Search Tree (OBST)

## Problem Statement

Given:

- `n` distinct sorted keys
- Successful-search probabilities `p1, p2, ..., pn`
- Dummy-key probabilities `q0, q1, ..., qn`

find the Binary Search Tree having the minimum expected search cost.

## Input

The program takes:

1. Number of keys `n`
2. `n` sorted keys
3. Successful search probabilities `p1...pn`
4. Dummy search probabilities `q0...qn`

Probabilities can be entered as decimal values.

## Example Input

```text
Enter number of keys: 3

Enter 3 sorted keys:
10 20 30

Enter successful search probabilities p1...p3:
0.3 0.2 0.1

Enter dummy search probabilities q0...q3:
0.05 0.05 0.1 0.2
```

## Approach

Dynamic Programming is used.

Define:

```text
e[i][j]
```

as the minimum expected search cost for keys `i` through `j`.

The algorithm considers every key between `i` and `j` as a possible root.

For every possible root `r`:

```text
cost =
    e[i][r-1]
    + e[r+1][j]
    + w[i][j]
```

The minimum cost is selected.

The `root[][]` table stores the optimal root for each interval.

## Algorithm

1. Read the number of keys.
2. Read the sorted keys.
3. Read successful probabilities `p`.
4. Read dummy probabilities `q`.
5. Initialize empty subtree costs.
6. Calculate probability weights.
7. Consider intervals of increasing length.
8. For each interval:
   - Try every key as root.
   - Calculate expected search cost.
   - Select the minimum.
9. Store the optimal root.
10. Print the minimum expected search cost.

## Output

The program prints:

- Minimum expected search cost
- Root key
- Root information for subtrees

## Complexity Analysis

The algorithm considers all possible roots for every possible interval.

- Time Complexity: **O(n³)**
- Space Complexity: **O(n²)**

## Concepts Used

- Dynamic Programming
- Binary Search Trees
- Optimal Substructure
- Probability
- Interval DP
- Cost Optimization

## File

```text
q8_obst.c
```
