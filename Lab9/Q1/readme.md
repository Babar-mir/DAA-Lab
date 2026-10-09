# Q1: Fractional Knapsack with Deterioration Rate

File: `q1_knapsack_decay.c`

## Problem

n items with value v_i, weight w_i and decay rate lambda_i > 0. An item consumed at time t has effective density `v_i/w_i - lambda_i*t`. Capacity W. Choose the consumption order and fractions to maximise total value.

## Assumptions / notes

The handout does not define time, so this program uses:

- Items are consumed one after another at 1 weight-unit per unit time, so a unit consumed after tau units of weight has value `d_i - lambda_i*tau` (d_i = v_i/w_i).
- If x_i units of item i start at time T_i, its block value is `d_i*x_i - lambda_i*(T_i*x_i + x_i^2/2)`.
- At most w_i units per item, at most W in total (stopping early is allowed).

## Input format (stdin)

`n W` on the first line, then `n` lines `v_i w_i lambda_i`.

## Algorithm

1. **Order (greedy):** swapping adjacent blocks i, j changes the value by `x_i*x_j*(lambda_i - lambda_j)`, so blocks must be consumed in decreasing lambda (fastest decay first), whatever the amounts.
2. **Amounts:** with that order the objective is `sum d_i x_i - 1/2 x^T M x` with `M_ij = min(lambda_i, lambda_j)`, a positive semi-definite matrix, so the problem is concave over `0<=x<=w, sum x<=W`. It is solved by projected FISTA; the gradient costs O(n) using prefix sums.
3. **Validation:** for a concave problem the KKT conditions are necessary and sufficient. The program prints the KKT residual (about 0 means optimal).

## Complexity

- Sorting: O(n log n).
- Optimisation: O(K \* n) for K iterations (each projection uses a fixed 100-step bisection, so O(100n) per iteration).
- Space: O(n).
- Not a closed-form greedy: the order is greedy, the amounts need numeric optimisation when supply and capacity interact.

## Edge cases

Needs `w_i > 0` and `lambda_i > 0`. Output is floating point (tolerance about 1e-9).

## Validation

Compared with SLSQP multi-start optimisation on 600 random instances, plus the KKT residual printed every run.

## Build and run

```
gcc -O2 -Wall -o q1 q1_knapsack_decay.c -lm
./q1 < tests/q1.in
```

## Sample

Input (`tests/q1.in`):

```
3 10
60 5 0.5
100 20 2
120 30 0.1
```

Output:

```
Optimal consumption schedule (fastest-decaying first)
item  lambda    start t    amount     fraction   value
1     0.5       0.0000     5.0000     1.0000     53.7500
3     0.1       5.0000     5.0000     0.1667     16.2500
Weight used = 10.0000 / 10.0000
MAXIMUM TOTAL VALUE = 70.000000
[validation] FISTA iterations = 5, KKT residual = 0.00e+00  (OPTIMAL)
```
