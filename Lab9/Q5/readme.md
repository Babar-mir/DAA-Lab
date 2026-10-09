# Q5: Candy Distribution (bi-directional slope greedy)

File: `q5_candy.c`

## Problem

Every child gets at least one candy, and a child with a higher rating than an immediate neighbour must get more candies than that neighbour. Minimise the total.

## Input format (stdin)

`n`, then `n` ratings.

## Algorithm

1. **Left pass:** `c[i] = c[i-1] + 1` if `r[i] > r[i-1]`, else 1.
2. **Right pass:** if `r[i] > r[i+1]`, set `c[i] = max(c[i], c[i+1] + 1)`.
3. The two passes enforce the two independent one-sided constraints, and taking the max satisfies both with no extra candies.
4. **Slope version (O(1) extra space):** track the length of the current up-slope, down-slope and the peak height; a down-slope longer than the peak height must lift the peak by one.

## Complexity

- Time: O(n). Space: O(n) for the two-pass version, O(1) extra for the slope version.

## Edge cases

Equal neighbours impose no constraint.

## Validation

Both methods are computed and compared, and the assignment is checked against the rule on every run.

## Build and run

```
gcc -O2 -Wall -o q5 q5_candy.c
./q5 < tests/q5.in
```

## Sample

Input (`tests/q5.in`):

```
5
1 0 2 2 1
```

Output:

```
Candies per child: 2 1 2 2 1
Minimum total candies = 8
[validation] one-pass slope method = 8  (MATCH)
[validation] rule check on assignment: OK
```
