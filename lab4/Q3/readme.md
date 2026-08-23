# Application of Sorting III

## Problem Statement

Given a set `S` of `n` integers, an integer `T`, and an integer `k`, determine whether there exist `k` integers in `S` whose sum is equal to `T`.

In other words, we need to determine whether:

```text
a1 + a2 + a3 + ... + ak = T
```

where all `a1, a2, ..., ak` are elements of `S`.

The required time complexity is:

```text
O(n^(k-1) log n)
```

---

## Approach

The main idea is to select `k-1` elements from the set and use **binary search** to find the final required element.

Suppose we have selected:

```text
a1, a2, ..., a(k-1)
```

Their sum is:

```text
sum = a1 + a2 + ... + a(k-1)
```

The required final element is:

```text
required = T - sum
```

We then perform binary search for `required` in the remaining part of the sorted array.

If the value is found, then:

```text
a1 + a2 + ... + a(k-1) + required = T
```

and a valid combination exists.

---

## Why Do We Sort the Array?

Binary search requires the input array to be sorted.

Therefore, the array is sorted before searching.

For example:

```text
Before sorting:
7 2 9 5 4

After sorting:
2 4 5 7 9
```

The sorting operation takes:

```text
O(n log n)
```

which does not exceed the required complexity for `k >= 2`.

---

## Algorithm

1. Read `n`.
2. Read the `n` elements of set `S`.
3. Read `k`.
4. Read the target value `T`.
5. Sort the array.
6. Recursively select `k-1` elements.
7. For every selection:
   - Calculate the sum of the selected elements.
   - Calculate:

     ```text
     required = T - sum
     ```

   - Perform binary search for `required`.

8. Search only after the index of the last selected element so that the same element is not selected more than once.
9. If the required element is found:
   - Print the complete combination.
   - Stop.

10. If no combination is found, print that no such combination exists.

---

## Example

### Input

```text
5
2 4 5 7 9
3
16
```

Here:

```text
S = {2, 4, 5, 7, 9}
k = 3
T = 16
```

We need to find three elements whose sum is `16`.

The algorithm selects:

```text
2 + 4
```

Required element:

```text
16 - 2 - 4 = 10
```

`10` is not present.

It then tries another combination:

```text
2 + 5
```

Required element:

```text
16 - 2 - 5 = 9
```

`9` is found using binary search.

Therefore:

```text
2 + 5 + 9 = 16
```

### Output

```text
Combination found:
2 5 9
```

---

## Example 2 — No Combination

### Input

```text
5
2 4 5 7 9
3
30
```

There are no three elements whose sum is `30`.

### Output

```text
No combination of 3 elements adds up to 30.
```

---

## Complexity Analysis

The algorithm selects `k-1` elements.

The number of possible selections is bounded by:

```text
O(n^(k-1))
```

For each selection, binary search is performed on the sorted array:

```text
O(log n)
```

Therefore, the total complexity is:

```text
O(n^(k-1) log n)
```

The initial sorting takes:

```text
O(n log n)
```

which is dominated by the main algorithm for `k >= 2`.

Therefore:

**Time Complexity: `O(n^(k-1) log n)`**

**Space Complexity: `O(n)`**

The space is used for the input array and the array storing the selected elements.

---

## Key Observation

The important idea is to avoid checking every possible set of `k` elements directly.

Instead:

```text
Select k-1 elements
        ↓
Calculate required element
        ↓
Binary search for required element
```

This reduces the problem to `O(n^(k-1))` selections, with an `O(log n)` binary search for each selection, giving the required:

```text
O(n^(k-1) log n)
```
