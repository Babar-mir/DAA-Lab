# Application of Sorting II

## Problem Statement

Given two sets `S1` and `S2`, each containing `n` elements, and a target number `x`, determine whether there exists a pair of elements such that:

- One element is selected from `S1`.
- One element is selected from `S2`.
- Their sum is equal to `x`.

Formally, we need to find whether:

```text
S1[i] + S2[j] = x
```

The required time complexity is:

```text
O(n log n)
```

---

## Approach

The input sets are given in **sorted order**.

For every element `a` in `S1`, we calculate the value that would be required from `S2`:

```text
required = x - a
```

We then perform a **binary search** for `required` in `S2`.

If the value is found, then:

```text
a + required = x
```

and the required pair exists.

If no required value is found for any element of `S1`, then no such pair exists.

---

## Algorithm

1. Read the size `n`.
2. Read the sorted set `S1`.
3. Read the sorted set `S2`.
4. Read the target value `x`.
5. For every element `S1[i]`:
   - Calculate:

     ```text
     required = x - S1[i]
     ```

   - Perform binary search for `required` in `S2`.

6. If binary search finds the required element:
   - Print the pair.
   - Stop the search.

7. If all elements of `S1` are checked without finding a pair:
   - Print that no such pair exists.

---

## Binary Search

Binary search is used because `S2` is already sorted.

For a search value `key`:

1. Set `left = 0`.
2. Set `right = n - 1`.
3. Calculate the middle index.
4. Compare `S2[mid]` with `key`.
5. If they are equal, the element is found.
6. If `S2[mid] > key`, search the left half.
7. Otherwise, search the right half.
8. Continue until the element is found or the search range becomes empty.

---

## Example

### Input

```text
5
1 3 5 7 9
2 4 6 8 10
13
```

Here:

```text
S1 = {1, 3, 5, 7, 9}
S2 = {2, 4, 6, 8, 10}
x = 13
```

### Processing

For the first element:

```text
required = 13 - 1
         = 12
```

`12` is not present in `S2`.

For the second element:

```text
required = 13 - 3
         = 10
```

`10` is present in `S2`.

Therefore:

```text
3 + 10 = 13
```

### Output

```text
Pair found:
3 from S1 + 10 from S2 = 13
```

---

## Example 2 — No Pair

### Input

```text
5
1 3 5 7 9
2 4 6 8 10
20
```

No element from `S1` has a corresponding element in `S2` whose sum is `20`.

### Output

```text
No such pair exists.
```

---

---

## Complexity Analysis

There are `n` elements in `S1`.

For each element, we perform binary search on `S2`.

Binary search takes:

```text
O(log n)
```

Since it is performed `n` times:

```text
O(n) × O(log n) = O(n log n)
```

Therefore:

**Time Complexity: `O(n log n)`**

**Space Complexity: `O(n)`**

The `O(n)` space is used to store the two input sets.

---

## Key Observation

The most important point is that the sets are **already sorted**.

If the sets were not sorted, we would first need to sort them, which would add an `O(n log n)` sorting step.

Here, because `S2` is already sorted, we can directly apply binary search and achieve the required **O(n log n)** algorithm.
