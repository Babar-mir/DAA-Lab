# DAA Lab-5 – Question 4

## Problem Statement

Implement Heap Sort to sort N randomly generated elements stored
in a file. Also perform the complexity analysis of the algorithm.

## Approach

The program generates N random integers and stores them in an
input file.

The elements are then read from the file and sorted using Heap Sort.

A Max Heap is constructed and the maximum element is repeatedly
removed from the heap and placed at the end of the array.

The sorted elements are finally stored in an output file.

## Input

The program takes:

1. Number of random elements N
2. Input file name
3. Output file name

## Output

- Randomly generated elements
- Sorted elements
- Sorted elements stored in the output file

## Algorithm

1. Read N.
2. Generate N random integers.
3. Store the integers in the input file.
4. Read the integers from the file.
5. Build a Max Heap.
6. Swap the root with the last element.
7. Reduce the heap size.
8. Apply heapify to restore the Max Heap.
9. Repeat until all elements are sorted.
10. Display the sorted array.
11. Store the sorted elements in the output file.

## Complexity Analysis

Build Heap: O(N)

Best-case Time Complexity: O(N log N)

Average-case Time Complexity: O(N log N)

Worst-case Time Complexity: O(N log N)

Auxiliary Space Complexity: O(1)

File Reading/Writing: O(N)

## Compilation

```bash
gcc q4_heap_sort_file.c -o q4
```
