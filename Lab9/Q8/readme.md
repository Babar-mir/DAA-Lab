# Q8: Minimum Number of Meeting Rooms

File: `q8_meeting_rooms.c`

## Problem

Given meeting intervals, find the minimum number of rooms so that no two overlapping meetings share a room.

## Input format (stdin)

`n`, then `n` lines `start end` with start < end.

## Algorithm

1. Sort all start times and all end times separately.
2. Walk through the starts. If the next start is before the earliest unfinished end, a new room is needed; otherwise that meeting reuses the room freed by the earliest end.
3. The answer is the peak number of simultaneously active meetings. A meeting ending exactly when another starts does not conflict.

## Complexity

- Time: O(n log n) for the two sorts plus an O(n) sweep. Space: O(n).

## Edge cases

n = 0 gives 0 rooms.

## Validation

An O(n^2) count of intervals alive at each start time is compared with the sweep on every run.

## Build and run

```
gcc -O2 -Wall -o q8 q8_meeting_rooms.c
./q8 < tests/q8.in
```

## Sample

Input (`tests/q8.in`):

```
4
0 30 5 10 15 20 25 40
```

Output:

```
Minimum meeting rooms = 2
[validation] brute-force max overlap = 2  (MATCH)
```
