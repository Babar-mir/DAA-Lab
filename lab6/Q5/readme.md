# DAA Lab-06 – Question 1

## Problem Statement

Given an unsorted integer array of n elements, determine the
worst-case complexity of:

1. Finding maximum
2. Finding first and second largest
3. Finding mean
4. Finding median
5. Finding standard deviation
6. Finding mode
7. Removing duplicates
8. Reversing the array
9. Partitioning with respect to a pivot

## Complexity

| Operation                | Complexity               |
| ------------------------ | ------------------------ |
| Maximum                  | O(n)                     |
| First and Second Largest | O(n)                     |
| Mean                     | O(n)                     |
| Median                   | O(n log n) using sorting |
| Standard Deviation       | O(n)                     |
| Mode                     | O(n²)                    |
| Remove Duplicates        | O(n²)                    |
| Reverse                  | O(n)                     |
| Partition                | O(n)                     |

## Input

- Number of elements
- Array elements
- Pivot element

## Output

The result of all nine operations.

## Compilation

```bash
gcc q1_array_operations.c -o q1 -lm
```
