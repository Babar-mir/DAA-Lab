DAA LAB-02
Dictionary Operations

Files:
  main.c    - six dictionary representations and timing program
  plot.gp   - GNUplot script for seven operation graphs

Compile:
  gcc -O2 main.c -o daa_lab02

Run:
  ./daa_lab02

Windows PowerShell:
  gcc -O2 main.c -o daa_lab02.exe
  .\daa_lab02.exe

Then plot:
  gnuplot plot.gp

The .dat files are generated automatically.

Complexities used (worst case):
Operation        UA    SA    SLU   SLS   DLU   DLS
Search           O(n)  O(logn) O(n) O(n) O(n) O(n)
Insert           O(1)  O(n)  O(1) O(n) O(1) O(n)
Delete           O(n)  O(n)  O(n) O(n) O(1) O(1)
Maximum         O(n)  O(1)  O(n) O(n) O(n) O(n)
Minimum         O(n)  O(1)  O(n) O(1) O(n) O(1)
Predecessor     O(n)  O(1)  O(n) O(n) O(n) O(1)
Successor       O(n)  O(1)  O(n) O(1) O(n) O(1)

Important:
- Predecessor/Successor are implemented with x already available,
  matching the lab statement Delete(D,x), Predecessor(D,x), etc.
- Sorted linked-list search is O(n), not O(log n), because linked lists
  do not support random access.
- Doubly linked Delete is O(1) because x is already a node pointer.
- The implementation stores only a head pointer for linked lists; therefore
  Maximum in a sorted linked list is O(n) because the tail is not stored.
