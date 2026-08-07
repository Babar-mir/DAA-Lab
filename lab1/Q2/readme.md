# Fair vs Biased Coin Simulation

## Aim

To implement a C program that simulates coin tossing and shows, through simulation, that the probability of HEAD for a fair coin is approximately 0.5, and to compare this against a biased coin.

## Problem Statement

Simulate tossing a fair coin a large number of times and show that the observed probability of HEAD approaches 0.5. Extend the simulation to a biased coin (unequal probability of HEAD/TAIL) and compare the two.

Example:

```
Input:
Number of tosses = 100000
Bias of second coin = 0.65

Output:
Fair coin   -> P(HEAD) ~ 0.50
Biased coin -> P(HEAD) ~ 0.65
```

## Approach

- A single function `tossCoin(p)` draws a uniform random number in [0, 1) and returns HEAD if the draw is less than `p`, otherwise TAIL.
- The same function is reused for both coins -- only the probability parameter changes: `p = 0.5` for the fair coin and `p = 0.65` for the biased coin.
- The simulation is repeated for increasing numbers of tosses (50 up to 500,000) to observe how the estimated probability converges to the true probability as the sample size grows (Law of Large Numbers).
- Results are written to a CSV file for plotting number of tosses (x-axis) against estimated P(HEAD) (y-axis) for both coins.

## Algorithm

1. Seed the random number generator using the current time.
2. For each sample size n in a list of increasing trial counts:
   - Toss the fair coin n times, count HEADs, compute the fraction.
   - Toss the biased coin n times, count HEADs, compute the fraction.
   - Print and store both estimated probabilities.
3. Write all results to `coin_simulation.csv`.
4. Observe that both estimates converge to their true probabilities as n increases.

## Concepts Used

- Random Number Generation (`rand()`)
- Probability and the Law of Large Numbers
- Simulation-based Analysis
- File Handling (CSV output for plotting)

## Sample Output

```
=====================================================
 Q2: Fair Coin vs Biased Coin (true bias = 0.65)
=====================================================
Tosses     Fair P(HEAD)     Biased P(HEAD)
-----------------------------------------------------
50         0.50000          0.76000
200        0.48500          0.68000
1000       0.50400          0.62200
5000       0.50900          0.65960
20000      0.50245          0.64680
100000     0.50140          0.65068
500000     0.50102          0.64953
-----------------------------------------------------
```

## Time Complexity

O(n) for a single simulation of n tosses. Across all tested sample sizes, the total cost is O(sum of all trial sizes).

## Space Complexity

O(1) additional space per simulation (just counters), plus O(k) to store results for k trial sizes before writing to file.

## Conclusion

The simulation confirms that as the number of tosses increases, the estimated probability of HEAD for a fair coin converges to 0.5, and for a biased coin converges to its true bias (0.65 here). This demonstrates the Law of Large Numbers in practice and shows how simulation can be used to empirically verify probabilistic claims.
