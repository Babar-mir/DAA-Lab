# DAA Lab-02 --- Question 2

## Merge Sort vs. Modified Merge Sort

### Problem Statement

Consider the following modification to Merge Sort:

-   Divide the input array into **three parts** instead of two.
-   Recursively sort each of the three parts.
-   Combine the three sorted parts using a **three-way merge**
    subroutine.

Determine the worst-case running time of the modified Merge Sort.

Write a C program to validate the theoretical claim by plotting the
order of growth of conventional Merge Sort and the modified three-way
Merge Sort.

------------------------------------------------------------------------

## 1. Objective

The objectives of this experiment are:

-   Implement conventional Merge Sort.
-   Implement modified three-way Merge Sort.
-   Derive the worst-case running time of the modified algorithm.
-   Measure the practical execution time of both algorithms.
-   Plot their order of growth using GNUplot.

------------------------------------------------------------------------

## 2. Conventional Merge Sort

Conventional Merge Sort divides an array into two approximately equal
parts.

``` text
                 n
               /                n/2   n/2
              |     |
            sort   sort
              \     /
              merge
```

The recurrence is:

``` text
T(n) = 2T(n/2) + Θ(n)
```

Using the Master Theorem:

``` text
a = 2
b = 2
f(n) = Θ(n)

n^(log_b(a)) = n^(log_2(2)) = n
```

Therefore:

``` text
T(n) = Θ(n log n)
```

------------------------------------------------------------------------

## 3. Modified Three-Way Merge Sort

The modified algorithm divides the array into three approximately equal
parts.

``` text
                    n
              /     |                 n/3    n/3    n/3
             |      |      |
           sort   sort   sort
              \     |     /
               3-way merge
```

The recurrence is:

``` text
T(n) = 3T(n/3) + Θ(n)
```

Using the Master Theorem:

``` text
a = 3
b = 3
f(n) = Θ(n)

n^(log_b(a)) = n^(log_3(3)) = n
```

Therefore:

``` text
T(n) = Θ(n log n)
```

------------------------------------------------------------------------

## 4. Why Is the Three-Way Merge Θ(n)?

In a normal merge, two sorted sequences are combined. Each element is
processed a constant number of times, so the merge takes `Θ(n)` time.

In a three-way merge, three sorted sequences are combined. At each step,
the smallest current element among the three sequences is selected.

The number of comparisons per element remains bounded by a constant.
Therefore:

``` text
Three-way merge = Θ(n)
```

Hence:

``` text
T(n) = 3T(n/3) + Θ(n)
```

and the overall complexity remains:

``` text
Θ(n log n)
```

------------------------------------------------------------------------

## 5. Complexity Comparison

  Algorithm          Recurrence                Worst-Case Time
  ------------------ ------------------------- -----------------
  Merge Sort         `T(n) = 2T(n/2) + Θ(n)`   `Θ(n log n)`
  3-Way Merge Sort   `T(n) = 3T(n/3) + Θ(n)`   `Θ(n log n)`

Both algorithms have the same asymptotic worst-case running time.

The practical running times can still differ because the three-way merge
performs more comparisons and has different implementation overhead.

------------------------------------------------------------------------

## 6. Experimental Validation

The C program measures the execution time of both algorithms for
increasing input sizes.

Example input sizes:

``` text
1000
2000
5000
10000
20000
50000
100000
200000
500000
1000000
```

The results are written to:

``` text
merge_comparison.dat
```

The file format is:

``` text
n    merge_sort_time    modified_merge_sort_time
```

The timing values depend on the system, compiler, optimization level,
and system load.

------------------------------------------------------------------------

## 7. Compilation

Using GCC:

``` bash
gcc -O2 -Wall -Wextra main.c -o main
```

Run:

``` bash
./main
```

On Windows:

``` powershell
gcc -O2 -Wall -Wextra main.c -o main.exe
.\main.exe
```

After execution, the program generates:

``` text
merge_comparison.dat
```

------------------------------------------------------------------------

## 8. GNUplot

A `.gp` file is **not required**. GNUplot commands can be entered
directly in the GNUplot terminal.

Start GNUplot:

``` bash
gnuplot
```

Then run:

``` gnuplot
set title "Merge Sort vs Modified 3-Way Merge Sort"
set xlabel "Input Size (n)"
set ylabel "Execution Time (microseconds)"
set grid

plot "merge_comparison.dat" using 1:2 with linespoints title "Merge Sort",      "merge_comparison.dat" using 1:3 with linespoints title "3-Way Merge Sort"
```

This plots the measured execution time of both algorithms against the
input size.

------------------------------------------------------------------------

## 9. Expected Observation

As the input size increases, the execution time of both algorithms
should show approximately `n log n` growth.

The two curves should therefore have a similar overall shape.

The three-way version may have a different constant factor because its
merge operation involves three sorted sequences rather than two.

Actual execution time can also be affected by:

-   Number of comparisons.
-   Memory allocation.
-   Cache behavior.
-   Compiler optimization.
-   Operating-system scheduling.
-   Implementation details.

Therefore, the graph should be used to experimentally support the
theoretical analysis.

------------------------------------------------------------------------

## 10. Conclusion

For conventional Merge Sort:

``` text
T(n) = 2T(n/2) + Θ(n)
```

Therefore:

``` text
T(n) = Θ(n log n)
```

For modified three-way Merge Sort:

``` text
T(n) = 3T(n/3) + Θ(n)
```

Therefore:

``` text
T(n) = Θ(n log n)
```

Thus, dividing the input into three parts instead of two **does not
change the asymptotic worst-case complexity**.

Both algorithms have:

``` text
Θ(n log n)
```

worst-case running time.

------------------------------------------------------------------------

## 11. Project Structure

``` text
Q2/
├── main.c
├── README.md
└── merge_comparison.dat
```

A GNUplot script can optionally be added as:

``` text
plot.gp
```

but it is not necessary because GNUplot commands can be entered
interactively.
