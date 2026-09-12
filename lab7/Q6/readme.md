# DAA Lab-07 – Question 6

## Problem Statement

Find the time/year when the largest number of prominent scientists
were alive.

The input consists of the birth and death years of the scientists.

If a person dies in the same year another person is born, the death
event is processed before the birth event.

## Approach

Each scientist generates two events:

Birth -> +1
Death -> -1

All events are sorted by year.

For equal years, death events are processed before birth events.

A sweep through the sorted events keeps track of the number of
scientists alive.

## Input

Number of scientists.

For each scientist:

Birth year
Death year

## Output

- Year with the maximum number of scientists alive
- Maximum number of scientists alive

## Complexity Analysis

Sorting: O(n log n)

Scanning: O(n)

Overall Time Complexity: O(n log n)

Space Complexity: O(n)

## Compilation

```bash
gcc q6_best_time_alive.c -o q6
```
