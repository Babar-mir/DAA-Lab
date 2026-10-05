# Edit Distance with Traceback

## Problem Statement

Given two strings `A` and `B`, determine the minimum number of operations required to transform `A` into `B`.

The allowed operations are:

1. Insertion
2. Deletion
3. Substitution

The program also prints the traceback operations used to obtain the minimum edit distance.

## Approach

Dynamic Programming is used.

Define:

```text
dp[i][j]
```

as the minimum number of operations required to transform the first `i` characters of `A` into the first `j` characters of `B`.

If:

```text
A[i-1] == B[j-1]
```

then:

```text
dp[i][j] = dp[i-1][j-1]
```

Otherwise:

```text
dp[i][j] =
1 + min(
    deletion,
    insertion,
    substitution
)
```

After calculating the DP table, traceback is performed from `dp[m][n]`.

## Input

The program takes:

1. Source string `A`
2. Target string `B`

## Output

The program prints:

- Minimum edit distance
- Traceback operations

## Example

### Input

```text
Enter source string: kitten
Enter target string: sitting
```

### Output

```text
Minimum Edit Distance = 3

Traceback:
Keep 'k'
Keep 'i'
Substitute 't' -> 's'
Keep 't'
Substitute 'e' -> 'i'
Keep 'n'
Insert 'g'
```

## Algorithm

1. Read strings `A` and `B`.
2. Find their lengths `m` and `n`.
3. Create an `(m+1) × (n+1)` DP table.
4. Initialize:
   - `dp[i][0] = i`
   - `dp[0][j] = j`
5. Fill the DP table.
6. If characters match, copy the diagonal value.
7. Otherwise consider insertion, deletion and substitution.
8. The final edit distance is `dp[m][n]`.
9. Perform traceback.
10. Print the operations.

## Complexity Analysis

- Time Complexity: **O(mn)**
- Space Complexity: **O(mn)**

## Concepts Used

- Dynamic Programming
- Edit Distance
- String Processing
- Traceback
- Reconstruction

## File

```text
q6_edit_distance.c
```
