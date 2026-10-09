# Q9: Hu-Tucker (optimal alphabetic binary tree)

File: `q9_hu_tucker.c`

## Problem

Build a binary tree whose leaves appear in the given order and `sum w_i * depth_i` is minimum.

## Input format (stdin)

`n`, then `n` weights in their fixed order (n <= 200).

## Algorithm

**Phase 1 (combination).** Keep a sequence of nodes. Original leaves are _square_, merged nodes are _circle_. Two nodes are _compatible_ if no square node lies strictly between them. Repeatedly merge the compatible pair with the smallest weight sum (ties: leftmost) and put the new circle node at the position of the left node. The tree built this way is not alphabetic, but it gives the correct leaf depths.

**Phase 2 (reconstruction).** Push leaves left to right with their depths onto a stack. While the top two entries have equal depth, merge them and lower the depth by one. This builds an order-preserving tree with the same cost.

## Complexity

- This implementation: O(n^2) pair scan per merge, O(n^3) total, O(n) space. Hu-Tucker can be made O(n log n) with priority queues.
- Validation DP: O(n^3) time, O(n^2) space.

## Edge cases

n = 1 gives cost 0 and a single leaf.

## Validation

Compared with the interval DP `C[i][j] = min_k C[i][k] + C[k+1][j] + W(i..j)` on 1500 random inputs; all matched.

## Build and run

```
gcc -O2 -Wall -o q9 q9_hu_tucker.c
./q9 < tests/q9.in
```

## Sample

Input (`tests/q9.in`):

```
6
8 2 4 1 9 3
```

Output:

```
Leaf depths (in input order): 2 3 4 4 2 2
Alphabetic tree: ((1 (2 (3 4))) (5 6))
Optimal cost sum(w_i*depth_i) = 66
[validation] interval-DP optimum = 66  (MATCH)
```
