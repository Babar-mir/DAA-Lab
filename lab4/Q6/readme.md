# Application of Sorting VI

## Problem Statement

Given a set `S` of `n` intervals on a line, where the `i`th interval is represented by its left and right endpoints:

```text
(li, ri)
```

we have to find a point `p` on the line that is contained in the **largest number of intervals**.

An endpoint is considered to be part of its interval.

The required time complexity is:

```text
O(n log n)
```

---

## Example

Consider:

```text
S = {(10,40), (20,60), (50,90), (15,70)}
```

The point:

```text
p = 50
```

is contained in:

```text
(20,60)
(50,90)
(15,70)
```

Therefore, `50` is contained in `3` intervals.

No point is contained in all four intervals.

Hence the maximum overlap is:

```text
3
```

---

## Approach

We use a **sweep-line algorithm**.

Each interval generates two events:

```text
Left endpoint  → +1
Right endpoint → -1
```

For an interval:

```text
(l, r)
```

we create:

```text
(l, +1)
(r, -1)
```

There are `2n` events in total.

We sort all events by their position and then scan them from left to right.

During the scan:

- At a left endpoint, increase the number of active intervals.
- At a right endpoint, the interval is still considered to contain that endpoint, so check the current count before decreasing it.
- Whenever the current number becomes greater than the previous maximum, store that position.

---

## Algorithm

1. Read `n`.
2. For every interval `(l, r)`:
   - Create event `(l, +1)`.
   - Create event `(r, -1)`.

3. Sort all `2n` events by their position.
4. Initialize:

   ```text
   current = 0
   maximum = 0
   ```

5. Scan the sorted events.
6. For a start event:
   - Increment `current`.
   - Check whether it is a new maximum.

7. For an end event:
   - Check the current count first because the endpoint belongs to the interval.
   - Decrement `current`.

8. Store the point where the maximum was obtained.
9. Print the point and the maximum number of intervals containing it.

---

## Example

### Input

```text
4
10 40
20 60
50 90
15 70
```

Events:

```text
10  +1
40  -1
20  +1
60  -1
50  +1
90  -1
15  +1
70  -1
```

After sorting:

```text
10  +1
15  +1
20  +1
40  -1
50  +1
60  -1
70  -1
90  -1
```

The running count is:

```text
Position    Count
10            1
15            2
20            3
40            2
50            3
60            2
70            1
90            0
```

The maximum number of overlapping intervals is:

```text
3
```

## A valid point is `20` or `50`.

## Complexity Analysis

There are `2n` events.

Sorting them takes:

```text
O(2n log(2n))
```

which simplifies to:

```text
O(n log n)
```

The sweep through all events takes:

```text
O(n)
```

Therefore:

```text
O(n log n) + O(n)
= O(n log n)
```

### Final Complexity

**Time Complexity:** `O(n log n)`

**Space Complexity:** `O(n)`

---

## Key Observation

The interval problem is converted into an endpoint-event problem:

```text
Left endpoint  → +1
Right endpoint → -1
```

After sorting the endpoints, the running count tells us how many intervals contain the current point.

The largest running count gives the required maximum overlap.
