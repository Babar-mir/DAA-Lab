# Element Uniqueness

## Aim

To implement C programs that check whether any duplicate elements exist in an array of n random numbers, and to analyze the efficiency of different approaches for sufficiently large n.

## Problem Statement

For a given array A with n elements containing random numbers, implement a method in C to check if any duplicates exist. Analyze what can be concluded about the method's efficiency for large n.

Example:

```
Input:
Array = [4, 2, 7, 2, 9]

Output:
Duplicate found: 2 appears more than once.
```

## Approach

Three different methods are implemented and compared:

1. **Brute Force** -- compare every pair of elements, O(n^2).
2. **Sort + Adjacent Scan** -- sort the array (`qsort`) then check neighboring elements, O(n log n).
3. **Hashing (Presence Array)** -- mark each value as "seen" in a boolean array indexed by value, O(n) average, at the cost of O(range) extra memory.

To keep the timing comparison fair, test arrays are generated as **guaranteed duplicate-free** (using a partial Fisher-Yates shuffle) rather than plain random generation -- with n in the thousands and a bounded value range, the birthday paradox makes a random duplicate almost certain, which would let brute force exit early and understate its true worst-case cost.

## Algorithm

1. Generate a duplicate-free array of n random values.
2. **Brute force:** for each pair (i, j) with i < j, compare `arr[i]` and `arr[j]`; stop and report a duplicate if found.
3. **Sort-based:** sort the array with `qsort`, then scan for any `arr[i] == arr[i+1]`.
4. **Hashing:** allocate a boolean array of size RANGE; for each element, check if it was already marked, else mark it.
5. Time all three methods for increasing values of n and record the results.

## Concepts Used

- Brute Force Search
- Sorting (`qsort` from `stdlib.h`)
- Hashing / Presence Arrays
- Time Complexity Analysis
- File Handling (CSV output for plotting)

## Sample Output

```
========================================================
 Q6: Element Uniqueness - Brute Force vs Sort vs Hashing
========================================================
n        BruteCmps        Brute(s)     Sort(s)      Hash(s)
--------------------------------------------------------
500      124750           0.000176     0.000064     0.000908
1000     499500           0.000580     0.000066     0.000132
2000     1999000          0.002173     0.000145     0.000106
4000     7998000          0.008783     0.000304     0.000169
8000     31996000         0.035362     0.000738     0.000132
```

## Time Complexity

- Brute Force: O(n^2)
- Sort + Adjacent Scan: O(n log n)
- Hashing (Presence Array): O(n) average

## Space Complexity

- Brute Force: O(1) additional space
- Sort + Adjacent Scan: O(1) to O(log n) (depending on `qsort` implementation)
- Hashing: O(RANGE), where RANGE is the size of the value domain -- only practical when the value range is known and bounded

## Conclusion

The brute-force method's runtime roughly quadruples every time n doubles, confirming its O(n^2) complexity, making it impractical for large n. The sort-based approach scales far better at O(n log n), while the hashing approach is fastest overall at O(n) average, though it trades time for extra memory proportional to the value range. For large n, hashing (when the range is bounded) or sorting (when it is not) are clearly preferable to brute force.
