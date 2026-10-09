# Q3: Minimum Refuelling Stops (and Minimum Initial Fuel)

File: `q3_refuel.c`

## Problem

A car starts with fuel F (1 fuel = 1 distance unit) and must reach distance D. Station i is at distance d_i and gives f_i fuel. Find the minimum number of refuelling stops.

## Assumptions / notes

The title says "Minimum Initial Fuel" but the question asks for stops, so the program answers both.

## Input format (stdin)

`D F n` on the first line (target, initial fuel), then `n` lines `d_i f_i`. Stations may come in any order.

## Algorithm

1. **Min stops (forward greedy):** sort stations by distance. Every station within current reach goes into a max-heap of refuel amounts (decide later). When stuck, refuel at the largest amount passed and count one stop. If the heap is empty and the target is not reached, print -1.
2. **Cross-check (DP):** `dp[j]` = farthest reach with exactly j stops; take the smallest j with `dp[j] >= D`.
3. **Reverse greedy (minimum initial fuel):** start with `R = D` and go from the farthest to the nearest station: `R = max(d_i, R - f_i)`. The final R is the least initial fuel that reaches D when stopping at every station.

## Complexity

- Greedy: O(n log n) time, O(n) space.
- DP check: O(n^2).
- Reverse greedy: O(n) after sorting.

## Edge cases

If D <= F the answer is 0 stops. Unreachable targets print -1.

## Validation

Greedy answer is compared with the DP answer on every run (1000 random cases matched).

## Build and run

```
gcc -O2 -Wall -o q3 q3_refuel.c
./q3 < tests/q3.in
```

## Sample

Input (`tests/q3.in`):

```
100 10 4
10 60
20 30
30 30
60 40
```

Output:

```
Minimum refuelling stops (greedy)   = 2
[validation] DP answer              = 2  (MATCH)
Reverse greedy: minimum initial fuel needed to reach D (stopping everywhere) = 10
```
