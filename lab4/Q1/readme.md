# Application of Sorting I

## Problem Statement

We are given `n` pairs of items. Each pair contains:

* A **number**
* One of three colours: **Red (R), Blue (B), or Yellow (Y)**

The input items are already sorted according to their numbers.

The task is to rearrange the items so that:

1. All **Red** items come first.
2. All **Blue** items come next.
3. All **Yellow** items come last.
4. The numbers within each colour must remain sorted.
5. The algorithm must run in **O(n)** time.

---

## Approach

Since the input is already sorted by number, we do not need to perform a comparison-based sorting algorithm.

We use three separate arrays:

```text
red[]
blue[]
yellow[]
```

We scan the input once.

For every item:

* If its colour is `R`, store it in `red[]`.
* If its colour is `B`, store it in `blue[]`.
* If its colour is `Y`, store it in `yellow[]`.

Finally, we print the three arrays in the order:

```text
Red → Blue → Yellow
```

### Why does the number order remain sorted?

The input is already sorted by number. Since we scan it from left to right and insert each item into its corresponding colour array, the numbers within each colour remain in their original sorted order.

---

## Algorithm

1. Read `n`.
2. Create three arrays for Red, Blue, and Yellow items.
3. Initialize counters:

   * `r = 0`
   * `b = 0`
   * `y = 0`
4. Read each `(number, colour)` pair.
5. Insert the pair into the appropriate array based on its colour.
6. Print all elements of `red[]`.
7. Print all elements of `blue[]`.
8. Print all elements of `yellow[]`.

---

## Example

### Input

```text
6
1 R
2 Y
3 B
4 R
5 B
6 Y
```

### Processing

```text
Red:
(1,R)
(4,R)

Blue:
(3,B)
(5,B)

Yellow:
(2,Y)
(6,Y)
```

### Output

```text
(1,R) (4,R) (3,B) (5,B) (2,Y) (6,Y)
```

The numbers inside each colour group are still sorted.

---

## Complexity Analysis

### Time Complexity

The input is scanned once and the resulting arrays are printed once.

```text
O(n)
```

### Space Complexity

Three arrays are used to store the elements.

```text
O(n)
```

---

## Conclusion

The problem can be solved in **O(n)** time because the input is already sorted by number and there are only three possible colours. By separating the items into three colour-specific arrays while scanning the input once, we obtain the required order without performing conventional sorting.
