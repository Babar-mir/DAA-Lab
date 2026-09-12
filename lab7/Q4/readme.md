# DAA Lab-07 – Question 4

## Problem Statement

There are n security switches. The rightmost switch can be
toggled freely. Other switches can only be toggled when the
switch immediately to their right is ON and all switches further
to the right are OFF.

Initially all switches are ON.

Find the minimum number of moves required to turn all switches OFF.

## Approach

The minimum number of moves follows:

S(1) = 1
S(2) = 2

For n >= 3:

S(n) = 2S(n-1) + 1 if n is odd
S(n) = 2S(n-1) if n is even

The closed form is:

S(n) = (2^(n+2) - (-1)^n - 3) / 6

## Input

Number of switches n.

## Output

Minimum number of moves.

## Complexity Analysis

Time Complexity: O(n)

Space Complexity: O(1)

## Compilation

```bash
gcc q4_security_switches.c -o q4
```
