---

# README.md — Q2

````markdown
# DAA Lab-06 – Question 2

## Problem Statement

Given n × n square matrices, implement and analyze:

1. Matrix Addition
2. Matrix Multiplication
3. Zero Matrix Check
4. Symmetric Matrix Check
5. Determinant
6. In-place Transpose
7. Eigenvalue and Eigenvector

## Complexity

| Operation           | Complexity |
| ------------------- | ---------- |
| Addition            | O(n²)      |
| Multiplication      | O(n³)      |
| Zero Matrix         | O(n²)      |
| Symmetric Matrix    | O(n²)      |
| Determinant         | O(n³)      |
| In-place Transpose  | O(n²)      |
| Dominant Eigenvalue | O(kn²)     |

## Input

- Matrix order n
- Matrix A
- Matrix B

## Output

Results of the matrix operations.

## Note

The eigenvalue/eigenvector implementation uses Power Iteration
and calculates the dominant eigenvalue and corresponding
eigenvector.

## Compilation

```bash
gcc q2_matrix_operations.c -o q2 -lm
```
````
