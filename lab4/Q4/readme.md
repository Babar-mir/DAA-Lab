# Application of Sorting IV

## Problem Statement

A camera at the door of a party records the entry time `ai` and exit time `bi` for each of `n` people.

For every person:

```text
bi > ai
```

Given these entry and exit times, determine the **maximum number of people that were simultaneously present at the party**.

All entry and exit times are distinct, so there are no ties.

The required time complexity is:

```text
O(n log n)
```

---

## Approach

Each person's interval can be represented using two events:

- Entry event → `+1`
- Exit event → `-1`

For a person with:

```text
entry = a
exit = b
```

we create:

```text
(a, +1)
(b, -1)
```

For `n` people, there are `2n` events.

We then sort all events according to their time.

After sorting, we scan the events from beginning to end.

For every event:

- If it is an entry, increase the current number of people.
- If it is an exit, decrease the current number of people.
- Keep track of the maximum value of the current number.

---

## Algorithm

1. Read the number of people `n`.
2. Create an array of `2n` events.
3. For each person:
   - Read the entry time `ai`.
   - Read the exit time `bi`.
   - Store `(ai, +1)` as an entry event.
   - Store `(bi, -1)` as an exit event.

4. Sort all `2n` events by their time.
5. Initialize:

   ```text
   current = 0
   maximum = 0
   ```

6. Traverse the sorted events.
7. Add the event type to `current`.
8. If `current > maximum`, update `maximum`.
9. Print `maximum`.

---

## Example

### Input

```text
4
1 5
2 7
4 6
8 10
```

The intervals are:

```text
Person 1: 1 → 5
Person 2: 2 → 7
Person 3: 4 → 6
Person 4: 8 → 10
```

The corresponding events are:

```text
1  +1
5  -1

2  +1
7  -1

4  +1
6  -1

8  +1
10 -1
```

After sorting:

```text
1  +1
2  +1
4  +1
5  -1
6  -1
7  -1
8  +1
10 -1
```

Scanning the events:

```text
Time    Change    Current
1       +1          1
2       +1          2
4       +1          3
5       -1          2
6       -1          1
7       -1          0
8       +1          1
10      -1          0
```

Therefore, the maximum number of simultaneously present people is:

```text
3
```

### Output

```text
Maximum number of people present simultaneously: 3
```

---

## Complexity Analysis

There are `2n` events.

Sorting these events takes:

```text
O(2n log(2n))
```

which simplifies to:

```text
O(n log n)
```

Scanning all events takes:

```text
O(n)
```

Therefore, the total time complexity is:

```text
O(n log n)
```

### Space Complexity

We store `2n` events:

```text
O(n)
```

Therefore:

**Time Complexity: `O(n log n)`**

**Space Complexity: `O(n)`**

---

## Key Observation

The problem can be converted from an interval problem into an event-sorting problem:

```text
Entry → +1
Exit  → -1
```

After sorting the events by time, the running sum directly represents the number of people currently present.

The maximum running sum gives the maximum number of people simultaneously present.
