# DAA Lab-5 – Question 3

## Problem Statement

Implement Quick Sort on N randomly generated elements stored in
a file.

## Approach

The program generates N random integers and stores them in an
input file.

The elements are then read from the file and sorted using
Randomized Quick Sort.

The sorted elements are finally stored in another output file.

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

1. Read N from the user.
2. Generate N random integers.
3. Store the integers in the input file.
4. Read the integers from the input file.
5. Select a random pivot.
6. Partition the array.
7. Recursively apply Quick Sort to the left and right partitions.
8. Display the sorted array.
9. Store the sorted array in the output file.

## Complexity Analysis

Expected/Average Time Complexity: O(N log N)

Worst-case Time Complexity: O(N^2)

Expected Space Complexity: O(log N)

File reading and writing: O(N)

## Compilation

```bash
gcc q3_quick_sort_file.c -o q3
```
