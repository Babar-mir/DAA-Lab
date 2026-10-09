# Q7: Minimise Deviation in Array

File: `q7_min_deviation.c`

## Problem

You may multiply an odd element by 2 or divide an even element by 2 any number of times. Minimise `max(A) - min(A)`.

## Input format (stdin)

`n`, then `n` positive integers.

## Algorithm

1. Double every odd element. Doubling is reversible by halving, so this starts from the largest possible state of every element.
2. Put everything in a max-heap and track the minimum.
3. Repeat: pop the maximum, record `max - min`; if the maximum is odd, stop; otherwise halve it, update the minimum, and push it back.
4. Only lowering the maximum can reduce the deviation, and that is only possible while the maximum is even.

## Complexity

- Time: O(n log n \* log M), since each element can be halved at most log M times and each heap operation costs O(log n).
- Space: O(n).

## Edge cases

Uses 64-bit integers because doubling an odd value can overflow 32 bits.

## Validation

Matched an exhaustive search over each element's reachable values on 1500 random small arrays.

## Build and run

```
gcc -O2 -Wall -o q7 q7_min_deviation.c
./q7 < tests/q7.in
```

## Sample

Input (`tests/q7.in`):

```
4
1 2 3 4
```

Output:

```
Minimum deviation = 1
```
