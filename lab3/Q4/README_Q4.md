# DAA Lab-03 — Question 4
## Matrix Multiplication using Divide and Conquer — Strassen's Method

### Problem Statement
Write a C program to multiply two square matrices of size `n × n` using Strassen's method.

### Objective
- Implement Strassen's divide-and-conquer matrix multiplication.
- Understand why it uses seven recursive multiplications instead of eight.
- Derive and validate the worst-case complexity.

### Strassen's Method
Partition:

```text
A = | A11 A12 |    B = | B11 B12 |
    | A21 A22 |        | B21 B22 |
```

Compute:

```text
P1 = (A11 + A22)(B11 + B22)
P2 = (A21 + A22)B11
P3 = A11(B12 - B22)
P4 = A22(B21 - B11)
P5 = (A11 + A12)B22
P6 = (A21 - A11)(B11 + B12)
P7 = (A12 - A22)(B21 + B22)
```

Then:

```text
C11 = P1 + P4 - P5 + P7
C12 = P3 + P5
C21 = P2 + P4
C22 = P1 - P2 + P3 + P6
```

### Complexity
Strassen's recurrence is:

```text
T(n) = 7T(n/2) + Θ(n²)
```

By the Master Theorem:

```text
T(n) = Θ(n^log₂7) ≈ Θ(n^2.807)
```

For comparison, conventional matrix multiplication is `Θ(n³)`.

### Input
The basic recursive implementation is most convenient for powers of two:

```text
2, 4, 8, 16, 32, 64, ...
```

For arbitrary `n`, zero-padding to the next power of two can be used.

### Compilation

```bash
gcc -O2 -Wall -Wextra strassen.c -o strassen
```

Windows:

```powershell
gcc -O2 -Wall -Wextra strassen.c -o strassen.exe
.\strassen.exe
```

### Experimental Validation
Record execution times for increasing matrix sizes in a file such as:

```text
n    strassen_time
2    ...
4    ...
8    ...
16   ...
32   ...
```

### GNUplot
A `.gp` file is not required.

```gnuplot
set title "Strassen Matrix Multiplication"
set xlabel "Matrix Size (n)"
set ylabel "Execution Time (microseconds)"
set grid
plot "strassen.dat" using 1:2 with linespoints title "Strassen"
```

### Conclusion
Strassen reduces recursive multiplications from eight to seven and achieves:

```text
Θ(n^log₂7) ≈ Θ(n^2.807)
```

which is asymptotically better than `Θ(n³)` conventional matrix multiplication.
