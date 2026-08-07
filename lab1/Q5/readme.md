# Find the Partition Point

## Aim

To implement a C program that finds the exact partition point in an array containing a sequence of 0s followed by 1s using the Binary Search algorithm.

## Problem Statement

Given an array of n elements where all the 0s appear before all the 1s, determine the exact point where the transition from 0 to 1 occurs.

Example:

```
Input:
0 0 1 1 1

Output:
Partition Point = 2
Transition occurs between index 2 and 3
```

## Approach

- Since the array is already sorted (all 0s followed by all 1s), Binary Search can be used to efficiently locate the first occurrence of 1.
- Whenever a 1 is found, store its index and continue searching in the left half to check if an earlier 1 exists.
- The first occurrence of 1 represents the partition point.
- A Linear Search version is also implemented alongside Binary Search, so the two approaches can be compared directly on the same input.

## Algorithm

1. Read the number of elements and the array.
2. Initialize:
   - `low = 0`
   - `high = n` (search space `[0, n]`, where `n` means "no 1 found")
3. Perform Binary Search:
   - Find the middle element.
   - If the middle element is 1, it may be the first 1 -- search the left half (`high = mid`).
   - Otherwise, the first 1 must be further right -- search the right half (`low = mid + 1`).
4. After the search:
   - If `low == n`, the array is all 0s (no partition point).
   - Otherwise, `low` is the index of the first 1 -- the partition point.

## Concepts Used

- Binary Search
- Linear Search (for comparison)
- Arrays
- Functions
- Time Complexity Analysis

## Sample Output

```
Enter array size: 5
Enter the 5 elements (0's followed by 1's):
0 0 1 1 1

Linear search: partition point (first 1) at index 2.
Binary search: partition point (first 1) at index 2.

-----------------------------------------------------
Comparison count on generated arrays (partition at n/2):
Size n     Linear (worst)     Binary (worst)
-----------------------------------------------------
1000       1000               10
10000      10000              14
100000     100000             17
```

## Time Complexity

O(log n)
The program uses Binary Search, reducing the search space by half in each iteration. (The Linear Search version used for comparison is O(n).)

## Space Complexity

O(1)
Only a few additional variables (`low`, `high`, `mid`) are used regardless of the input size.

## Conclusion

This program successfully identifies the partition point in an array containing consecutive 0s followed by 1s. By using Binary Search, the solution achieves an efficient time complexity of O(log n), making it suitable even for large input sizes -- as shown in the comparison table, binary search needs only 17 comparisons for an array of 100,000 elements, versus up to 100,000 for a linear scan.
