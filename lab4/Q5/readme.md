# Application of Sorting V

## Problem Statement

Given a list `I` of `n` intervals, where each interval is represented as:

```text
(xi, yi)
```

we have to merge all overlapping intervals and return the resulting list.

For example:

```text
I = {(1,3), (2,6), (8,10), (7,18)}
```

The output should be:

```text
{(1,6), (7,18)}
```

The algorithm should run in worst-case:

```text
O(n log n)
```

---

## Approach

The intervals are first sorted according to their left endpoints.

After sorting, overlapping intervals will occur next to each other.

For every interval:

- If its left endpoint is less than or equal to the right endpoint of the last merged interval, the two intervals overlap.
- Extend the right endpoint of the merged interval if necessary.
- Otherwise, store the interval as a new separate interval.

---

## Algorithm

1. Read `n`.
2. Read all `n` intervals.
3. Sort the intervals according to their left endpoint.
4. Store the first interval as the first merged interval.
5. Traverse the remaining intervals.
6. For every interval:
   - Check whether:

     ```text
     current.left <= lastMerged.right
     ```

   - If true, merge the intervals.
   - Otherwise, add the interval as a new merged interval.

7. Print all merged intervals.

---

## Example

### Input

```text
4
1 3
2 6
8 10
7 18
```

After sorting:

```text
(1,3)
(2,6)
(7,18)
(8,10)
```

Processing:

```text
(1,3) and (2,6)
        ↓
     overlap
        ↓
     (1,6)
```

Then:

```text
(1,6) and (7,18)
        ↓
   no overlap
```

Finally:

```text
(7,18) and (8,10)
        ↓
     overlap
        ↓
     (7,18)
```

Therefore:

```text
(1,6) (7,18)
```

---

## Complexity Analysis

Sorting `n` intervals takes:

```text
O(n log n)
```

The merging process requires one traversal:

```text
O(n)
```

Therefore:

```text
O(n log n) + O(n)
= O(n log n)
```

### Final Complexity

**Time Complexity:** `O(n log n)`

**Space Complexity:** `O(n)`

---

## Key Observation

The main idea is:

```text
Sort intervals
      ↓
Compare adjacent intervals
      ↓
Merge if they overlap
      ↓
Continue until all intervals are processed
```

Sorting is what allows the overlapping intervals to be processed efficiently in a single subsequent scan.
