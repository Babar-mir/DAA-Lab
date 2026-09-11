# DAA Lab-5 – Question 2

## Problem Statement

Find the Kth smallest element in a given list of N numbers without
sorting the list.

## Approach

The program uses the Quickselect algorithm.

Quickselect is based on the partition technique of Quick Sort,
but unlike Quick Sort, it recursively processes only the part of
the array that contains the required Kth smallest element.

The complete array is therefore not sorted.

## Input

- Number of elements N
- N integer elements
- Value of K

## Output

The Kth smallest element.

## Algorithm

1. Read N and the array.
2. Read K.
3. Partition the array around a pivot.
4. Determine the position of the pivot.
5. If the pivot position is K, return the pivot.
6. If K is smaller, search in the left part.
7. Otherwise, search in the right part.
8. Display the Kth smallest element.

## Complexity Analysis

Average Time Complexity: O(N)

Worst-case Time Complexity: O(N^2)

Space Complexity: O(N) in the worst case due to recursion.

## Compilation

```bash
gcc q2_kth_smallest.c -o q2