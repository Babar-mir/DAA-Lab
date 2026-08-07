# Towers of Hanoi (ToH)

## Aim

To implement a C program that simulates the solution to the Tower of Hanoi problem, counts the total number of moves required for n discs, and analyzes the growth of the move count as n increases.

## Problem Statement

Simulate the solution to the Tower of Hanoi problem for n discs using recursion in C. Plot the total number of moves required against n and draw a conclusion about the algorithm's efficiency.

Example:

```
Input:
n = 3 discs

Output:
Move 1: disc 1  A -> C
Move 2: disc 2  A -> B
Move 3: disc 1  C -> B
Move 4: disc 3  A -> C
Move 5: disc 1  B -> A
Move 6: disc 2  B -> C
Move 7: disc 1  A -> C

Total moves = 7
```

## Approach

- The classic recursive strategy is used: to move n discs from a source rod to a destination rod using an auxiliary rod, first move the top (n-1) discs to the auxiliary rod, then move the largest disc to the destination, then move the (n-1) discs from the auxiliary rod onto the destination.
- A global counter is incremented every time a disc is moved, giving the total move count for a given n.
- The program prints every move for a small, user-chosen n, and separately tabulates the move count for n = 1 to 25 using the closed-form result moves = 2^n - 1, writing the results to a CSV file for plotting.

## Algorithm

1. Read n (number of discs) from the user.
2. Call `solveHanoi(n, from, aux, to)`:
   - If n == 0, return (base case).
   - Recursively call `solveHanoi(n-1, from, to, aux)`.
   - Move disc n from `from` to `to`, increment move counter.
   - Recursively call `solveHanoi(n-1, aux, from, to)`.
3. Print the total move count for the chosen n.
4. Separately compute `moves = 2^n - 1` for n = 1 to 25 and write to `tower_of_hanoi.csv`.

## Concepts Used

- Recursion
- Divide and Conquer
- Exponential Time Complexity
- File Handling (CSV output for plotting)

## Sample Output

```
=====================================================
 Q4: Tower of Hanoi
=====================================================
Enter number of discs to simulate step-by-step (try 3 or 4): 3
Move 1   : disc 1  A -> C
Move 2   : disc 2  A -> B
Move 3   : disc 1  C -> B
Move 4   : disc 3  A -> C
Move 5   : disc 1  B -> A
Move 6   : disc 2  B -> C
Move 7   : disc 1  A -> C
-----------------------------------------------------
Total moves for 3 discs = 7
```

## Time Complexity

O(2^n) -- the number of moves (and recursive calls) doubles roughly every time n increases by 1, since `T(n) = 2*T(n-1) + 1`, which solves to `T(n) = 2^n - 1`.

## Space Complexity

O(n) for the recursion call stack (recursion depth equals the number of discs).

## Conclusion

The program confirms that the Tower of Hanoi requires exactly `2^n - 1` moves for n discs, growing exponentially with n. Doubling n roughly squares the move count, making the problem computationally impractical for large n (e.g. 25 discs already require over 33 million moves) despite the recursive algorithm itself being short and simple to implement. This makes Tower of Hanoi a classic example of an O(2^n) algorithm.
