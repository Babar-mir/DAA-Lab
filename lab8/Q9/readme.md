# Collatz Conjecture

## Problem Statement

The Collatz Conjecture defines the following recurrence for a positive integer `n`:

```text
If n is even:
    n = n / 2

If n is odd:
    n = 3n + 1
```

The process is repeatedly applied until `n = 1`.

The conjecture states that every positive integer eventually reaches `1`, but this has not been mathematically proven.

The program experimentally analyzes the trajectory of a user-provided starting value and can also analyze all values in an interval `[a,b]`.

## Objective

The program demonstrates:

- Iterative control structures
- Functional decomposition
- Dynamic memory / pointer concepts
- Integer overflow handling
- Arithmetic trajectory analysis

The lab specifically presents this as an open unsolved problem.

## Input

The program provides two choices:

```text
1. Analyze a single starting value
2. Analyze an interval [a,b]
```

### Single Value

The user enters a positive integer `n`.

### Interval

The user enters:

```text
a
b
```

where:

```text
a <= b
```

## Output

For a single value, the program displays:

- Complete trajectory
- Number of steps
- Maximum value reached

For an interval, it displays:

- Steps for each starting value
- Maximum value reached by each trajectory
- Number having the largest trajectory
- Largest number of steps
- Number producing the largest value
- Largest value reached

## Example — Single Value

### Input

```text
Enter your choice: 1
Enter starting value n (> 0): 13
```

### Output

```text
Trajectory for 13:
13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1

Starting value : 13
Total steps    : 9
Maximum value  : 40
```

## Example — Interval

### Input

```text
Enter your choice: 2
Enter interval start a: 1
Enter interval end b: 5
```

### Output

```text
n = 1 | steps = 0 | max = 1
n = 2 | steps = 1 | max = 2
n = 3 | steps = 7 | max = 16
n = 4 | steps = 2 | max = 4
n = 5 | steps = 5 | max = 16
```

## Algorithm

### Single Trajectory

1. Read starting value `n`.
2. Check that `n > 0`.
3. While `n != 1`:
   - If `n` is even, divide by `2`.
   - Otherwise calculate `3n + 1`.
   - Count the step.
   - Track the maximum value.
4. Stop when `n = 1`.
5. Display the results.

### Interval Analysis

1. Read `a` and `b`.
2. For every starting value from `a` to `b`:
   - Generate its Collatz trajectory.
   - Count its steps.
   - Find its maximum value.
3. Track the value with:
   - Largest number of steps.
   - Largest trajectory value.
4. Display the summary.

## Overflow Handling

For odd values, calculating:

```text
3n + 1
```

can overflow the integer data type.

Therefore, the program checks whether the operation is safe before performing it.

If an overflow would occur, the program reports:

```text
OVERFLOW
```

## Complexity Analysis

For a starting value `n`, let `T(n)` represent the number of iterations required to reach `1`.

- Time Complexity: **O(T(n))**
- Auxiliary Space: **O(1)**

For an interval `[a,b]`:

```text
O(Σ T(x))
```

for all `x` from `a` to `b`.

## Concepts Used

- Iteration
- Functions
- Unsigned Integer Types
- Overflow Detection
- Modular Program Design
- Arithmetic Sequences
- Dynamic Analysis

## File

```text
q9_collatz.c
```
