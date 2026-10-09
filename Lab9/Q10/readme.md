# Q10: Greedy Superstring Conjecture (experimentation tool)

File: `q10_greedy_superstring.c`

## Problem

Find the shortest string containing every input string as a substring. This is NP-hard; the greedy algorithm (merge the pair with maximum overlap) is conjectured to be a 2-approximation, an open problem.

## Assumptions / notes

This is an exploration tool, not a solution to the open problem. The handout says a September 2026 arXiv paper disproves the conjecture (ratio approaching 9/4) but that the claim is not yet validated. I have not verified it; read the paper before citing it.

## Input format (stdin)

Normal mode: `n` (<= 16), then `n` strings (<= 127 characters each).
Search mode: `./q10 --search trials n maxlen alphabet seed`.

## Algorithm

1. **Preprocess:** drop duplicates and strings that are substrings of another.
2. **Greedy:** repeatedly merge the ordered pair with the largest suffix/prefix overlap (ties: first found).
3. **Exact optimum:** Held-Karp bitmask DP over overlaps, `dp[mask][last]` = shortest superstring covering `mask` and ending with string `last`; the answer string is rebuilt from parent pointers.
4. Print greedy length, optimal length and the ratio. `--search` tries random instances and reports the worst ratio found.

## Complexity

- Preprocessing: O(n^2 L).
- Greedy (naive): O(n^3 L).
- Exact: O(2^n n^2) time, O(2^n n) space (n <= 16).

## Edge cases

Greedy's output can depend on tie-breaking. Random inputs only produced ratios around 1.1; counterexamples to the 2-approximation need carefully built instances.

## Validation

Greedy is compared against the exact optimum on every run, so the ratio is always reported correctly.

## Build and run

```
gcc -O2 -Wall -o q10 q10_greedy_superstring.c
./q10 < tests/q10.in
```

## Sample

Input (`tests/q10.in`):

```
5
abcde cdefg efgab ghabc fgh
```

Output:

```
After removing contained/duplicate strings: 5 strings
Greedy superstring  (len 12): fghabcdefgab
Optimal superstring (len 12): fghabcdefgab
Approximation ratio greedy/optimal = 1.0000   (conjecture says <= 2; handout claims a counterexample approaching 2.25)
```
