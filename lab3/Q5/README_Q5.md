# DAA Lab-03 — Question 5
## Multiplying Special-Pattern Square Matrices using Divide and Conquer

### Problem Statement
Two `n × n` matrices are given, where `n = 2^k`. Each matrix has the recursive structure:

```text
M = | M1 M2 |
    | M2 M1 |
```

where `M1` and `M2` have the same structure recursively down to single elements. Develop a divide-and-conquer multiplication algorithm with `O(n²)` running time.

### Objective
Exploit the repeated block structure instead of treating the matrices as arbitrary matrices.

### Derivation
Let:

```text
A = | A1 A2 |    B = | B1 B2 |
    | A2 A1 |        | B2 B1 |
```

Then:

```text
AB = | A1B1 + A2B2   A1B2 + A2B1 |
     | A1B2 + A2B1   A1B1 + A2B2 |
```

Define:

```text
R = A1B1 + A2B2
S = A1B2 + A2B1
```

Then:

```text
AB = | R S |
     | S R |
```

Only four recursive multiplications are needed:

```text
A1 × B1
A2 × B2
A1 × B2
A2 × B1
```

### Complexity
The recurrence is:

```text
T(n) = 4T(n/2) + Θ(n²)
```

Since:

```text
n^(log₂4) = n²
```

we obtain:

```text
T(n) = Θ(n²)
```

### Input
Use powers of two:

```text
1, 2, 4, 8, 16, 32, ...
```

### Compilation

```bash
gcc -O2 -Wall -Wextra special_matrix.c -o special_matrix
```

Windows:

```powershell
gcc -O2 -Wall -Wextra special_matrix.c -o special_matrix.exe
.\special_matrix.exe
```

### Experimental Validation
Record timing for increasing `n` in:

```text
special_matrix.dat
```

Format:

```text
n    execution_time
2    ...
4    ...
8    ...
16   ...
```

### GNUplot

```gnuplot
set title "Special-Pattern Matrix Multiplication"
set xlabel "Matrix Size (n)"
set ylabel "Execution Time (microseconds)"
set grid
plot "special_matrix.dat" using 1:2 with linespoints title "Special Matrix D&C"
```

For order of growth:

```gnuplot
set logscale xy
plot "special_matrix.dat" using 1:2 with linespoints title "Experimental"
```

### Conclusion
The recursive symmetry reduces the number of recursive multiplications to four. Therefore:

```text
T(n) = Θ(n²)
```

which meets the required `O(n²)` bound.
