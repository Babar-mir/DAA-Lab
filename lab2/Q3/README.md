# DAA Lab-02 — Question 3
## Merging k Sorted Arrays

### Problem Statement

Suppose we are given `k` sorted arrays, each containing `n` elements, and we want to combine them into a single sorted array containing `kn` elements.

Two methods are considered.

### Method 1

Repeatedly use the merge subroutine:

```text
merge(A1, A2)
merge(result, A3)
merge(result, A4)
...
merge(result, Ak)
```

Determine the worst-case running time.

### Method 2

First divide the `k` arrays into `k/2` pairs and merge each pair. This produces `k/2` sorted arrays, each containing `2n` elements.

Repeat the process until only one sorted array containing `kn` elements remains.

Determine the running time as a function of `n` and `k`.

The C program validates the theoretical results experimentally.

---

## 1. Objective

The objectives are:

- Implement Method 1 using repeated merging.
- Implement Method 2 using pairwise merging.
- Derive the worst-case running time of both methods.
- Measure their execution time for increasing values of `k`.
- Plot the experimental growth using GNUplot.
- Compare the experimental results with the theoretical complexity.

---

# 2. Method 1 — Sequential Merging

Suppose there are `k` arrays:

```text
A1 A2 A3 A4 ... Ak
```

First:

```text
A1 + A2
```

contains `2n` elements.

Then:

```text
(A1 + A2) + A3
```

contains `3n` elements.

Then:

```text
((A1 + A2) + A3) + A4
```

contains `4n` elements.

This continues until all `k` arrays are merged.

The amount of work is approximately:

```text
2n + 3n + 4n + ... + kn
```

Therefore:

```text
T(n,k) = Θ(n(2 + 3 + ... + k))
```

Using:

```text
2 + 3 + ... + k = Θ(k²)
```

we obtain:

```text
T(n,k) = Θ(nk²)
```

Therefore:

```text
Method 1 = Θ(nk²)
```

---

# 3. Method 2 — Pairwise Merging

In Method 2, arrays are merged in rounds.

Initially:

```text
k arrays of size n
```

After the first round:

```text
k/2 arrays of size 2n
```

After the second round:

```text
k/4 arrays of size 4n
```

After the third round:

```text
k/8 arrays of size 8n
```

Eventually:

```text
1 array of size kn
```

For one complete round, every element participates in exactly one merge.

Therefore, the total work per round is:

```text
Θ(kn)
```

The number of rounds is:

```text
log₂ k
```

Therefore:

```text
T(n,k) = Θ(kn log k)
```

Thus:

```text
Method 2 = Θ(kn log k)
```

---

# 4. Complexity Comparison

| Method | Description | Worst-Case Time |
|---|---|---|
| Method 1 | Sequential merging | `Θ(nk²)` |
| Method 2 | Pairwise merging | `Θ(kn log k)` |

For the same `n` and large `k`:

```text
nk²
```

grows much faster than:

```text
nk log k
```

Therefore Method 2 is asymptotically more efficient.

---

# 5. Example

Suppose:

```text
k = 8
n = 100
```

### Method 1

The merge sizes are:

```text
200, 300, 400, 500, 600, 700, 800
```

Total work is proportional to:

```text
100(2 + 3 + 4 + 5 + 6 + 7 + 8)
```

which is:

```text
Θ(nk²)
```

### Method 2

The rounds are:

```text
Round 1:
8 arrays → 4 arrays

Round 2:
4 arrays → 2 arrays

Round 3:
2 arrays → 1 array
```

There are:

```text
log₂(8) = 3
```

rounds.

Each round processes all `kn = 800` elements.

Therefore:

```text
Θ(800 × 3)
```

which corresponds to:

```text
Θ(nk log k)
```

---

# 6. Experimental Validation

The C program keeps `n` fixed and varies `k`.

The default value is:

```text
n = 1000
```

The tested values of `k` are:

```text
2
4
8
16
32
64
128
```

Powers of two are used because Method 2 naturally divides the arrays into equal pairs at every round.

The program measures the execution time of both methods and writes the results to:

```text
q3_comparison.dat
```

The file format is:

```text
k    method1_time    method2_time
```

---

# 7. Compilation

Using GCC:

```bash
gcc -O2 -Wall -Wextra merging_k_sorted_arrays.c -o merging_k_sorted_arrays
```

On Windows:

```powershell
gcc -O2 -Wall -Wextra merging_k_sorted_arrays.c -o merging_k_sorted_arrays.exe
```

Run:

```powershell
.\merging_k_sorted_arrays.exe
```

The program first performs a correctness test and then generates timing data.

---

# 8. Correctness Test

The program checks that the output of both methods is sorted.

It prints:

```text
Method 1 sorted: YES
Method 2 sorted: YES
```

This verifies that both algorithms correctly produce a sorted array.

---

# 9. GNUplot

A `.gp` file is not required.

Start GNUplot:

```bash
gnuplot
```

Make sure GNUplot is in the directory containing:

```text
q3_comparison.dat
```

You can verify the current directory with:

```gnuplot
pwd
```

If necessary:

```gnuplot
cd "D:/path/to/Q3"
```

Then plot the measured execution times:

```gnuplot
set title "Merging k Sorted Arrays"
set xlabel "Number of Arrays (k)"
set ylabel "Execution Time (microseconds)"
set grid

plot "q3_comparison.dat" using 1:2 with linespoints title "Method 1: Sequential", \
     "q3_comparison.dat" using 1:3 with linespoints title "Method 2: Pairwise"
```

---

# 10. Plotting on a Logarithmic X-Axis

Because the tested values of `k` double:

```text
2, 4, 8, 16, 32, 64, 128
```

a logarithmic x-axis can make the growth easier to observe.

Use:

```gnuplot
set logscale x 2

set title "Merging k Sorted Arrays"
set xlabel "Number of Arrays (k)"
set ylabel "Execution Time (microseconds)"
set grid

plot "q3_comparison.dat" using 1:2 with linespoints title "Method 1: Sequential", \
     "q3_comparison.dat" using 1:3 with linespoints title "Method 2: Pairwise"
```

---

# 11. Theoretical Growth

For fixed `n`:

### Method 1

```text
T(k) = Θ(k²)
```

### Method 2

```text
T(k) = Θ(k log k)
```

Therefore, when plotting execution time against `k`, Method 1 should eventually grow substantially faster than Method 2.

---

# 12. Important Experimental Note

The measured execution times are affected by:

- CPU speed.
- Compiler optimization.
- Operating-system scheduling.
- Memory allocation.
- Cache behavior.
- Number of repetitions.
- Implementation details.

Therefore, individual measurements may not perfectly follow the theoretical curves.

The important observation is the **overall order of growth**.

For a stronger experiment, increase the input size `n` and repeat each measurement several times.

---

# 13. Conclusion

For Method 1, the total amount of merging is:

```text
Θ(n(2 + 3 + ... + k))
```

Therefore:

```text
┌─────────────────────┐
│ Method 1 = Θ(nk²)  │
└─────────────────────┘
```

For Method 2, there are `log₂ k` merging rounds, and every round processes all `kn` elements:

```text
Θ(kn) × Θ(log k)
```

Therefore:

```text
┌────────────────────────┐
│ Method 2 = Θ(kn log k) │
└────────────────────────┘
```

Hence Method 2 is asymptotically more efficient than Method 1 for large `k`.

---

# 14. Project Structure

```text
Q3/
├── merging_k_sorted_arrays.c
├── README.md
└── q3_comparison.dat
```

A GNUplot `.gp` file is optional. GNUplot commands can be entered directly in the terminal.
