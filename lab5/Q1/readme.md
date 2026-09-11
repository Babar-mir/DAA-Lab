# DAA Lab-5 – Question 1

## Problem Statement

Find the median of a list of N numbers without sorting the list.
Also perform the complexity analysis of the algorithm.

## Approach

The program uses the Quickselect algorithm to find the required
order statistic without completely sorting the array.

- For odd N, the median is the (N/2 + 1)th smallest element.
- For even N, the median is the average of the N/2th and
  (N/2 + 1)th smallest elements.

## Input

- Number of elements N
- N integer elements

## Output

The median of the given elements.

## Algorithm

1. Read N and the elements.
2. If N is odd:
   - Find the (N/2 + 1)th smallest element using Quickselect.
3. If N is even:
   - Find the N/2th smallest element.
   - Find the (N/2 + 1)th smallest element.
   - Calculate their average.
4. Display the median.

## Complexity Analysis

Average Time Complexity: O(N)

Worst-case Time Complexity: O(N^2)

Space Complexity: O(N) in the worst case due to recursion.

## Compilation

```bash
gcc q1_median.c -o q1
```
