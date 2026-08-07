# Order of Growth of Functions

## Aim

To implement a C program that determines the increasing order of growth of a given set of 12 functions for sufficiently large values of n.

## Problem Statement

Given 12 functions of n (e.g. `n log2n`, `12*sqrt(n)`, `1/n`, `n^log2n`, `100n^2+6n`, `n^0.51`, `n^2-324`, `50n^0.5`, `2n^3`, `3^n`, `2^32n`, `log2n`), arrange them in increasing order of asymptotic growth rate.

Example:

```
Input:
n = 100

Output (ranking, smallest to largest):
1/n < log2(n) < n^0.51 < 12*sqrt(n) < 50*n^0.5 < n*log2(n)
< n^2-324 < 100n^2+6n < 2n^3 < 2^32*n < n^log2(n) < 3^n
```

## Approach

- Several of the given functions (`n^log2n`, `3^n`, `2^32 * n`) become astronomically large even for moderate n, which overflows a normal `double` if computed directly.
- Since only the _relative order_ of the functions matters, the program instead computes `log10(f(n))` for every function.
- `log10` is a strictly increasing function, so sorting by `log10(value)` gives exactly the same order as sorting by the raw value, while keeping every number small and finite.
- The 12 log10-values are then sorted using Insertion Sort and printed for several increasing values of n, so the ranking can be observed as n grows.

## Algorithm

1. Choose a set of test values of n (e.g. 10, 100, 1000, ..., 10^8).
2. For each value of n:
   - Compute `log10(f(n))` for all 12 functions.
   - Handle edge cases (e.g. `n^2 - 324` is negative for small n; `log2(n)` requires n > 1).
3. Sort the 12 (function, log10-value) pairs using Insertion Sort.
4. Print the sorted ranking for that value of n.
5. Repeat for all chosen test values and compare the rankings to the theoretical order.

## Concepts Used

- Asymptotic Notation / Order of Growth
- Insertion Sort
- Logarithms (used to avoid overflow, not just for `log(n)` functions)
- Arrays and Structures
- Functions

## Sample Output

```
----- Ranking at n = 10 -----
 1. n^2-324        (log10 value = -100.000)
 2. 1/n            (log10 value = -1.000)
 3. n^0.51         (log10 value = 0.510)
 4. log2(n)        (log10 value = 0.521)
 5. n*log2(n)      (log10 value = 1.521)
 6. 12*sqrt(n)     (log10 value = 1.579)
 7. 50*n^0.5       (log10 value = 2.199)
 8. 2n^3           (log10 value = 3.301)
 9. n^log2(n)      (log10 value = 3.322)
10. 100n^2+6n      (log10 value = 4.003)
11. 3^n            (log10 value = 4.771)
12. 2^32 * n       (log10 value = 10.633)

...

----- Ranking at n = 100000000 -----
 1. 1/n            (log10 value = -8.000)
 2. log2(n)        (log10 value = 1.415)
 3. n^0.51         (log10 value = 4.080)
 4. 12*sqrt(n)     (log10 value = 5.079)
 5. 50*n^0.5       (log10 value = 5.699)
 6. n*log2(n)      (log10 value = 9.424)
 7. n^2-324        (log10 value = 16.000)
 8. 2^32 * n       (log10 value = 17.633)
 9. 100n^2+6n      (log10 value = 18.000)
10. 2n^3           (log10 value = 24.301)
11. n^log2(n)      (log10 value = 212.603)
12. 3^n            (log10 value = 47712125.472)
```

## Time Complexity

O(m log m) for ranking m = 12 functions (using Insertion Sort, this is O(m^2), but m is a small constant here so it is effectively O(1) per test value of n). Evaluating each function is O(1), so the dominant cost across all test values is O(k \* m^2), where k is the number of test values of n.

## Space Complexity

O(m), where m = 12, for storing the function names and their log10-values. No additional space grows with n.

## Conclusion

This program ranks 12 functions by asymptotic growth using a log10-scale comparison to avoid overflow from extremely large values. It shows that for small n, constants can make a "smaller order" function look larger than a "bigger order" one, but as n grows the true theoretical order always dominates -- confirming the standard hierarchy of growth rates used in algorithm analysis.
