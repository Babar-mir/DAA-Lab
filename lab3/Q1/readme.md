# Binary Search vs Ternary Search

**Course:** Design and Analysis of Algorithms (DAA)
**Lab Topic:** Comparative analysis of Binary Search and Ternary Search

---

## 1. Problem Statement

In binary search, an `n`-element sorted list is divided into nearly two equal
halves at each step. In ternary search, it is divided into nearly three equal
intervals. Design and implement a C program to search for an element `x` in a
sorted list of size `n` using both binary and ternary search. Justify and
validate whether binary search is better than ternary search via the
implementation.

---

## 2. Files

| File                    | Description                                                        |
| ----------------------- | ------------------------------------------------------------------ |
| `timing.c`              | C source implementing both algorithms, benchmarking harness        |
| `plot.gp`               | Gnuplot script to plot the benchmark results                       |
| `timing_data.txt`       | Generated benchmark output (input size vs average time per search) |
| `search_comparison.png` | Generated plot: time taken vs input size for both algorithms       |

---

## 3. Approach

### 3.1 Algorithms

- **Binary search:** repeatedly computes `mid = l + (r-l)/2` and discards one
  of two halves based on a single comparison against `arr[mid]`.
- **Ternary search:** computes two midpoints, `mid1` and `mid2`, splitting the
  range into three parts, and discards one of three parts based on up to
  four comparisons per iteration.

### 3.2 Benchmarking method

Since a single search on an array completes in nanoseconds — too fast to
measure reliably with `clock()`'s tick resolution — each algorithm is run
**2000 times per input size** on a mix of random targets (half guaranteed
present, half guaranteed absent), and the total time is divided by 2000 to
get an average time per search. This is repeated for input sizes ranging
from 1,000 to 50,000,000 elements.

A `volatile` accumulator (`sink`) is used to collect each search's return
value. This is necessary because the compiler (`-O2`) is otherwise free to
notice the search results are unused and delete the benchmarking loop
entirely (dead code elimination), which silently produces meaningless
all-zero timings.

---

## 4. Compilation and Execution

```bash
# Compile
gcc -O2 -o timing timing.c

# Run (generates timing_data.txt)
./timing

# Plot the results (requires gnuplot)
gnuplot plot.gp
```

This produces `search_comparison.png` — a log-scale plot of input size (x)
vs average time per search in microseconds (y), for both algorithms.

---

## 5. Results

| n          | Binary (µs) | Ternary (µs) |
| ---------- | ----------- | ------------ |
| 1,000      | 0.062       | 0.056        |
| 5,000      | 0.078       | 0.077        |
| 10,000     | 0.081       | 0.073        |
| 50,000     | 0.101       | 0.100        |
| 100,000    | 0.129       | 0.096        |
| 500,000    | 0.171       | 0.132        |
| 1,000,000  | 0.177       | 0.174        |
| 5,000,000  | 0.444       | 0.353        |
| 10,000,000 | 0.680       | 0.525        |
| 50,000,000 | 0.956       | 0.720        |

![Binary vs Ternary Search timing](search_comparison.png)

---

## 6. Analysis: Is Binary Search Better?

**Theoretically (comparison count):** binary search performs `O(log₂ n)`
iterations with 1 comparison each in the ideal case (≈ `2·log₂ n` total
comparisons), while ternary search performs `O(log₃ n)` iterations with up
to 4 comparisons each (≈ `4·log₃ n` total comparisons). Working this out:

```
Binary:  ≈ 2·log₂n
Ternary: ≈ 4·log₃n = 4·log₂n / log₂3 ≈ 2.52·log₂n
```

So by **raw comparison count**, binary search is theoretically more
efficient — this is the standard textbook argument.

**Empirically (measured wall-clock time):** the benchmark shows the
opposite — **ternary search is consistently faster than binary search
across every tested input size**, and the gap widens as `n` grows (at
n = 50,000,000: ternary ≈ 0.72 µs vs binary ≈ 0.96 µs per search).

**Why the theory and the measurement disagree:**

- Ternary search does fewer _loop iterations_ than binary search
  (`log₃ n` vs `log₂ n`, roughly 37% fewer for the same `n`), even though
  each iteration does more comparisons.
- Each iteration's dominant cost on real hardware is not the comparison
  itself but the **memory access** to `arr[mid]` — once the array is
  larger than cache size, this is a cache miss, which is far more
  expensive than a few extra register-level comparisons.
- Fewer iterations means fewer expensive memory accesses, which outweighs
  the cost of a couple of extra cheap comparisons per iteration — so
  ternary search wins in practice on this hardware.

**Conclusion:** Binary search is theoretically better by comparison count,
which is the metric most textbooks use to justify it, and it remains
preferable in practice for other reasons — simpler code, fewer branches to
get wrong, and it's what every standard library (`bsearch`, `std::binary_search`)
implements. But this benchmark shows the naive "binary search is faster"
claim does **not** hold up when measuring actual wall-clock time: the
measured data contradicts it, and the discrepancy is explained by
iteration count and cache behavior dominating over raw comparison count on
modern hardware.

---

## 7. Notes / Caveats

- Results depend on hardware (CPU cache sizes, branch predictor) and
  compiler optimization level; re-running on different hardware may shift
  the crossover point or even reverse the trend for small `n`.
- `clock()` measures CPU time, not wall-clock time; for this CPU-bound
  workload the two are effectively equivalent.
- The array is synthetically generated (`arr[i] = i*2`) and already sorted
  by construction; no separate sort step is required for this benchmark.
