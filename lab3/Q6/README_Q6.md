# DAA Lab-03 — Question 6
## Loop Invariants in Sorting — Selection Sort

### Problem Statement
Sort `n` numbers stored in `A[1...n]` by repeatedly finding the smallest element in the remaining unsorted portion and exchanging it with the first element of that portion. Explain the loop invariant, prove correctness using initialization, maintenance and termination, derive the running time, and implement the algorithm in C.

### Algorithm
This is Selection Sort.

```text
SelectionSort(A, n)

for i = 0 to n-2
    minIndex = i
    for j = i+1 to n-1
        if A[j] < A[minIndex]
            minIndex = j
    exchange A[i] and A[minIndex]
```

### Loop Invariant
At the beginning of iteration `i`, the first `i` elements are sorted and contain the `i` smallest elements of the entire array.

### Initialization
Before the first iteration, `i = 0`. The sorted portion contains zero elements, so the invariant is trivially true.

### Maintenance
During iteration `i`, the minimum element of `A[i...n-1]` is found and placed at `A[i]`. Therefore the first `i+1` elements are sorted and contain the `i+1` smallest elements.

### Termination
After the loop reaches `i = n-2`, the first `n-1` elements are correctly positioned. The final remaining element must also be in its correct position, so the whole array is sorted.

### Why Only `n-1` Iterations?
Once the first `n-1` elements are correctly placed, there is only one element left. It must occupy the final position automatically.

### Number of Comparisons
The comparisons are:

```text
(n-1) + (n-2) + ... + 1
```

Therefore:

```text
C(n) = n(n-1)/2
```

Hence:

```text
Best Case  = Θ(n²)
Worst Case = Θ(n²)
```

The best case is not asymptotically better because Selection Sort still scans the complete remaining portion even when the input is already sorted.

### Space Complexity
Selection Sort is in-place and uses only constant extra storage:

```text
Space = Θ(1)
```

### Compilation

```bash
gcc -O2 -Wall -Wextra selection_sort.c -o selection_sort
```

Windows:

```powershell
gcc -O2 -Wall -Wextra selection_sort.c -o selection_sort.exe
.\selection_sort.exe
```

### Experimental Validation
Generate data containing:

```text
n    actual_comparisons    theoretical_comparisons
10   45                   45
20   190                  190
50   1225                 1225
100  4950                 4950
```

The actual number of comparisons should exactly equal `n(n-1)/2`.

### GNUplot

```gnuplot
set title "Selection Sort - Number of Comparisons"
set xlabel "Input Size (n)"
set ylabel "Number of Comparisons"
set grid
plot "selection_sort.dat" using 1:2 with linespoints title "Actual Comparisons", \
     x*(x-1)/2 title "n(n-1)/2"
```

For an order-of-growth plot:

```gnuplot
set logscale xy
set title "Order of Growth of Selection Sort"
set xlabel "Input Size (n)"
set ylabel "Number of Comparisons"
plot "selection_sort.dat" using 1:2 with linespoints title "Actual"
```

### Conclusion
The loop invariant proves the correctness of Selection Sort. The algorithm performs exactly:

```text
n(n-1)/2
```

comparisons for every input arrangement. Therefore both best-case and worst-case running times are:

```text
Θ(n²)
```

with `Θ(1)` auxiliary space.
