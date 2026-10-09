# Q4: Minimum Cost to Connect Sticks

File: `q4_connect_sticks.c`

## Problem

Joining sticks of lengths x and y costs x + y and produces a stick of length x + y. Find the minimum total cost to join all sticks.

## Input format (stdin)

`n`, then `n` stick lengths.

## Algorithm

1. Put all lengths in a min-heap.
2. Pop the two shortest sticks, add their sum to the cost, push the sum back. Repeat until one stick remains.
3. **Why it works:** a stick's length is paid once per merge it takes part in, i.e. its depth in the merge tree. The two shortest sticks can be placed at the deepest level, which is exactly the Huffman exchange argument.

## Complexity

- Time: O(n log n). Space: O(n).

## Edge cases

n = 1 gives cost 0. Uses 64-bit integers.

## Validation

For n <= 3000 an O(n^2) naive version recomputes the answer and the program prints MATCH or MISMATCH.

## Build and run

```
gcc -O2 -Wall -o q4 q4_connect_sticks.c
./q4 < tests/q4.in
```

## Sample

Input (`tests/q4.in`):

```
4
2 4 3 5
```

Output:

```
Minimum total cost = 28
[validation] naive O(n^2) merge = 28  (MATCH)
```
