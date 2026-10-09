# Q2: Huffman Coding (canonical codebook)

File: `q2_huffman.c`

## Problem

Given symbol frequencies, build a prefix-free binary code of minimum expected length and print the canonical codebook (codes ordered by length, then lexicographically by symbol).

## Input format (stdin)

`n` (1 to 256), then `n` lines `symbol frequency` (symbol is a single non-space character).

## Algorithm

1. Put all symbols in a min-heap keyed by (frequency, creation order), so ties are deterministic.
2. Repeatedly pop the two smallest nodes and push their merge. The two least-frequent symbols can always be taken as the deepest siblings (exchange argument).
3. Read off only the code **lengths** from the tree (n = 1 gets length 1).
4. **Canonical assignment:** sort by (length, symbol). The first code is all zeros; each next code is `(previous + 1) << (len - prevLen)`. This is done on a bit string, so lengths over 63 also work.

## Complexity

- Time: O(n log n). Space: O(n).
- Canonical assignment: O(n log n) sort plus O(sum of code lengths).

## Edge cases

A single symbol gets code `0`. Frequencies of 0 are accepted and still receive a code.

## Validation

Prints the Kraft sum (must be 1 for a full prefix code) and compares expected length with entropy (H <= L < H+1).

## Build and run

```
gcc -O2 -Wall -o q2 q2_huffman.c -lm
./q2 < tests/q2.in
```

## Sample

Input (`tests/q2.in`):

```
6
a 45
b 13
c 12
d 16
e 9
f 5
```

Output:

```
Canonical Huffman codebook
symbol  freq       len  code
a       45         1    0
b       13         3    100
c       12         3    101
d       16         3    110
e       9          4    1110
f       5          4    1111
Total encoded bits = 224
Expected length = 2.240000 bits/symbol, entropy = 2.219880  (H <= L < H+1)
[validation] Kraft sum = 1.000000000000  (complete prefix code)
```
