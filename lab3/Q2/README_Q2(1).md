# DAA Lab-03 — Question 2
## Search the Defective Coin

### Problem Statement

There are `n` coins. All coins have exactly the same required weight except possibly one coin that may be lighter. The task is to find the lighter defective coin, if one exists, or report that no coin is defective.

A balance weighing scale is available. The required algorithm should find the defective coin, if present, or report none, in:

```text
O(log2 n)
```

time, more precisely `log2 n + c` for a positive constant `c`.

---

## 1. Key Idea

The important observation is that the problem has a **binary-search structure**.

Divide the possible coins into two equal groups and place the two groups on the balance.

There are three possible outcomes:

### Left side lighter

The defective coin is in the left group.

```text
Left < Right
```

### Right side lighter

The defective coin is in the right group.

```text
Right < Left
```

### Balance

Both groups have equal weight. Since there is at most one lighter defective coin, there is no defective coin in the current candidate set.

For arbitrary `n`, the implementation pads the set to the next power of two with known perfect dummy coins. If the final selected candidate is a dummy coin, the result is reported as "no defective coin."

---

## 2. Why the Running Time Is O(log n)

At every weighing, the number of possible candidates is approximately halved:

```text
n
n/2
n/4
n/8
...
1
```

The number of halvings required is:

```text
log2(n)
```

Therefore:

```text
T(n) = T(n/2) + O(1)
```

and:

```text
T(n) = O(log2 n)
```

The padding to the next power of two adds only a constant-level overhead to the asymptotic result.

---

## 3. Example

Suppose there are 8 coins and coin 6 is defective.

```text
Coins: 1 2 3 4 5 6 7 8
```

First weighing:

```text
1 2 3 4  vs  5 6 7 8
```

If the right side is lighter, the defective coin is among:

```text
5 6 7 8
```

Second weighing:

```text
5 6  vs  7 8
```

If the left side is lighter:

```text
5 6
```

Third weighing:

```text
5 vs 6
```

The lighter coin is identified.

Maximum number of weighings:

```text
log2(8) = 3
```

---

## 4. Important Assumption

The algorithm assumes:

- All normal coins have identical weight.
- At most one coin is defective.
- A defective coin is lighter, never heavier.
- The balance can determine which side is lighter or whether both sides balance.

---

## 5. Compilation

```bash
gcc -O2 -Wall -Wextra defective_coin.c -o defective_coin
```

On Windows:

```powershell
gcc -O2 -Wall -Wextra defective_coin.c -o defective_coin.exe
.\defective_coin.exe
```

The program includes examples for:

1. A set containing a lighter defective coin.
2. A set in which all coins are perfect.

---

## 6. Conclusion

The candidate set is halved after every useful weighing.

Therefore:

```text
T(n) = T(n/2) + O(1)
```

and:

```text
┌───────────────────────┐
│ T(n) = O(log2 n)     │
└───────────────────────┘
```

Thus the required logarithmic bound is achieved.
