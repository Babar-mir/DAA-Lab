# Performance Analysis of Bubble Sort

## Aim

To implement two versions of Bubble Sort in C -- one that terminates early once the array becomes sorted, and one that always completes all (n-1) passes -- and to analyze their efficiency by comparing the number of comparisons performed.

## Problem Statement

Implement (i) a Bubble Sort that stops as soon as a pass makes no swaps (the array is already sorted), and (ii) a Bubble Sort that always runs the full (n-1) passes regardless. Plot the number of comparisons made by both versions to analyze their efficiency.

Example:

```
Input:
Array = [1, 2, 3, 4, 5]   (already sorted, n = 5)

Output:
Early-exit version : 4 comparisons (stops after 1 pass)
Full-pass version   : 10 comparisons (always completes n-1 passes)
```

## Approach

- Both variants use the standard Bubble Sort swap logic; they differ only in whether a `swapped` flag is checked after each pass to break out early.
- Four kinds of input are generated for testing: sorted, nearly-sorted (one pair swapped), random, and reverse-sorted -- so the benefit of early termination is visible across different scenarios.
- A comparison counter is incremented on every element comparison in both versions, for array sizes n = 100 to 1000.
- Results are written to a CSV file for plotting comparisons against n, separately for each input type.

## Algorithm

1. Generate the array for a given input type (sorted / nearly-sorted / random / reverse).
2. Run the early-exit Bubble Sort:
   - For each pass, compare adjacent elements, swap if out of order, set `swapped = 1`.
   - If no swap occurred in a pass, break out of the loop.
3. Run the full-pass Bubble Sort on a fresh copy of the same array, always completing all (n-1) passes.
4. Record the comparison count for both versions.
5. Repeat for all input types and array sizes, writing results to `bubble_sort_analysis.csv`.

## Concepts Used

- Bubble Sort (with and without early termination)
- Best-case / Worst-case Analysis
- Arrays
- File Handling (CSV output for plotting)

## Sample Output

```
================================================================
 Q3: Bubble Sort - Early Exit vs Always-Full-Passes
================================================================
InputType      n        EarlyExit        FullPasses
----------------------------------------------------------------
Sorted         100      99               4950
NearlySorted   100      197              4950
Random         100      4895             4950
Reverse        100      4950             4950
----------------------------------------------------------------
```

## Time Complexity

- Early-exit version: O(n) best case (already sorted), O(n^2) worst case (reverse sorted).
- Full-pass version: O(n^2) in all cases, since it never checks whether the array is already sorted.

## Space Complexity

O(1) additional space for both versions (in-place sorting), plus O(n) for the input array itself.

## Conclusion

The early-exit version of Bubble Sort performs significantly fewer comparisons on sorted or nearly-sorted input, achieving close to O(n) in the best case, while the full-pass version always performs O(n^2) comparisons regardless of input order. On random or reverse-sorted input, both versions perform similarly, since the array never becomes fully sorted before the last possible pass. This confirms that early termination is a simple but effective optimization for Bubble Sort on partially-ordered data.
