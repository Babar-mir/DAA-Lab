---

# README.md — Q3

````markdown
# DAA Lab-06 – Question 3

## Problem Statement

Find the convolution of two vectors using an O(n log n)
divide-and-conquer algorithm.

The lengths of the vectors are m and n, where n >= m.

## Approach

FFT (Fast Fourier Transform) is used.

Convolution can be calculated by:

1. Taking FFT of A.
2. Taking FFT of B.
3. Performing point-wise multiplication.
4. Taking inverse FFT.

## Complexity

FFT: O(n log n)

Point-wise multiplication: O(n)

Overall:

O(n log n)

## Input

- Size of vector A
- Size of vector B
- Elements of A
- Elements of B

The condition n >= m is enforced.

## Output

Convolution vector C.

## Compilation

```bash
gcc q3_convolution.c -o q3 -lm
```
````
