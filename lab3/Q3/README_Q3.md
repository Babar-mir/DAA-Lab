# DAA Lab-03 — Question 3
## Maximum and Minimum Using Divide and Conquer

### Problem Statement

Using the divide-and-conquer approach, develop an algorithm to find both the maximum and minimum elements of an array of size `n` such that the number of comparisons is bounded by:

```text
3n/2
```

Implement the algorithm in C and validate the result.

---

## 1. Objective

The objectives are:

- Find both maximum and minimum elements.
- Use divide and conquer.
- Minimize the number of comparisons.
- Count the comparisons performed by the algorithm.
- Verify experimentally that the number of comparisons is at most `3n/2`.

---

## 2. Divide-and-Conquer Algorithm

For an array with one element:

```text
minimum = maximum = the only element
```

No comparison is required.

For two elements:

```text
compare the two elements once
```

The smaller element is the minimum and the larger element is the maximum.

For more than two elements:

1. Divide the array into two halves.
2. Recursively find the minimum and maximum of each half.
3. Compare the two maximum values.
4. Compare the two minimum values.

Only two comparisons are required to combine the results of the two halves.

---

## 3. Recurrence

Let `C(n)` be the number of comparisons.

For even `n`:

```text
C(n) = 2C(n/2) + 2
```

For `n = 2`:

```text
C(2) = 1
```

Solving the recurrence for powers of two gives:

```text
C(n) = 3n/2 - 2
```

Therefore:

```text
C(n) < 3n/2
```

and the required bound is satisfied.

---

## 4. Why This Is Better Than the Naive Method

A straightforward method could find the maximum and minimum separately.

Finding maximum requires:

```text
n - 1 comparisons
```

Finding minimum requires:

```text
n - 1 comparisons
```

Total:

```text
2n - 2 comparisons
```

The divide-and-conquer algorithm uses approximately:

```text
3n/2
```

comparisons, which is significantly smaller.

For large `n`:

```text
2n - 2 > 3n/2
```

approximately.

---

## 5. Example

For:

```text
A = {43, 90, 12, 44, 23, 7, 81, 55}
```

The algorithm divides the array recursively and combines the results.

Final result:

```text
Minimum = 7
Maximum = 90
```

For `n = 8`, the theoretical comparison bound is:

```text
3n/2 = 12
```

The exact divide-and-conquer count is:

```text
3n/2 - 2 = 10
```

comparisons.

Thus:

```text
10 <= 12
```

and the bound is satisfied.

---

## 6. Experimental Validation

The program counts the actual number of comparisons.

It generates:

```text
max_min_comparisons.dat
```

with columns:

```text
n    comparisons    theoretical_3n_over_2
```

Example:

```text
2       ...
4       ...
8       ...
16      ...
32      ...
64      ...
128     ...
256     ...
512     ...
1024    ...
```

---

## 7. Compilation

```bash
gcc -O2 -Wall -Wextra max_min_divide_conquer.c -o max_min_divide_conquer
```

On Windows:

```powershell
gcc -O2 -Wall -Wextra max_min_divide_conquer.c -o max_min_divide_conquer.exe
.\max_min_divide_conquer.exe
```

---

## 8. GNUplot

A `.gp` file is not required.

Start GNUplot:

```bash
gnuplot
```

Then:

```gnuplot
set title "Comparisons in Divide-and-Conquer Max-Min"
set xlabel "Input Size (n)"
set ylabel "Number of Comparisons"
set grid

plot "max_min_comparisons.dat" using 1:2 with linespoints title "Actual Comparisons", \
     "max_min_comparisons.dat" using 1:3 with linespoints title "3n/2 Bound"
```

The actual comparison curve should remain below the `3n/2` bound.

For powers of two, the exact result should follow:

```text
3n/2 - 2
```

---

## 9. Complexity

### Time complexity

The algorithm visits every element through the recursive decomposition:

```text
T(n) = 2T(n/2) + O(1)
```

Therefore:

```text
T(n) = O(n)
```

### Space complexity

The recursion depth is:

```text
O(log n)
```

Therefore the auxiliary recursion stack requires:

```text
O(log n)
```

space.

---

## 10. Conclusion

The divide-and-conquer algorithm finds both the maximum and minimum in linear time.

For powers of two, its comparison count is:

```text
C(n) = 3n/2 - 2
```

which satisfies:

```text
C(n) <= 3n/2
```

Thus the required comparison bound is validated.

The algorithm improves upon finding maximum and minimum independently, which requires:

```text
2n - 2
```

comparisons.

---

## 11. Project Structure

```text
Q2/
├── defective_coin.c
└── README.md

Q3/
├── max_min_divide_conquer.c
├── README.md
└── max_min_comparisons.dat
```

GNUplot scripts are optional because plotting commands can be entered directly in the GNUplot terminal.
