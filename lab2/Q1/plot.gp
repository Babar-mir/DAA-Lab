# DAA Lab-02 GNUplot script
# Data columns: n search insert delete max min predecessor successor

set datafile commentschars "#"
set grid
set key outside
set xlabel "Input size (n)"
set ylabel "Time (microseconds / operation)"
set terminal pngcairo size 1200,800

# Search
set output "search.png"
set title "Search Operation"
plot \
    "unsorted_array.dat" using 1:2 with linespoints title "Unsorted Array", \
    "sorted_array.dat" using 1:2 with linespoints title "Sorted Array", \
    "singly_unsorted.dat" using 1:2 with linespoints title "Singly Unsorted", \
    "singly_sorted.dat" using 1:2 with linespoints title "Singly Sorted", \
    "doubly_unsorted.dat" using 1:2 with linespoints title "Doubly Unsorted", \
    "doubly_sorted.dat" using 1:2 with linespoints title "Doubly Sorted"

# Insert
set output "insert.png"
set title "Insert Operation"
plot \
    "unsorted_array.dat" using 1:3 with linespoints title "Unsorted Array", \
    "sorted_array.dat" using 1:3 with linespoints title "Sorted Array", \
    "singly_unsorted.dat" using 1:3 with linespoints title "Singly Unsorted", \
    "singly_sorted.dat" using 1:3 with linespoints title "Singly Sorted", \
    "doubly_unsorted.dat" using 1:3 with linespoints title "Doubly Unsorted", \
    "doubly_sorted.dat" using 1:3 with linespoints title "Doubly Sorted"

# Delete
set output "delete.png"
set title "Delete Operation"
plot \
    "unsorted_array.dat" using 1:4 with linespoints title "Unsorted Array", \
    "sorted_array.dat" using 1:4 with linespoints title "Sorted Array", \
    "singly_unsorted.dat" using 1:4 with linespoints title "Singly Unsorted", \
    "singly_sorted.dat" using 1:4 with linespoints title "Singly Sorted", \
    "doubly_unsorted.dat" using 1:4 with linespoints title "Doubly Unsorted", \
    "doubly_sorted.dat" using 1:4 with linespoints title "Doubly Sorted"

# Maximum
set output "maximum.png"
set title "Maximum Operation"
plot \
    "unsorted_array.dat" using 1:5 with linespoints title "Unsorted Array", \
    "sorted_array.dat" using 1:5 with linespoints title "Sorted Array", \
    "singly_unsorted.dat" using 1:5 with linespoints title "Singly Unsorted", \
    "singly_sorted.dat" using 1:5 with linespoints title "Singly Sorted", \
    "doubly_unsorted.dat" using 1:5 with linespoints title "Doubly Unsorted", \
    "doubly_sorted.dat" using 1:5 with linespoints title "Doubly Sorted"

# Minimum
set output "minimum.png"
set title "Minimum Operation"
plot \
    "unsorted_array.dat" using 1:6 with linespoints title "Unsorted Array", \
    "sorted_array.dat" using 1:6 with linespoints title "Sorted Array", \
    "singly_unsorted.dat" using 1:6 with linespoints title "Singly Unsorted", \
    "singly_sorted.dat" using 1:6 with linespoints title "Singly Sorted", \
    "doubly_unsorted.dat" using 1:6 with linespoints title "Doubly Unsorted", \
    "doubly_sorted.dat" using 1:6 with linespoints title "Doubly Sorted"

# Predecessor
set output "predecessor.png"
set title "Predecessor Operation"
plot \
    "unsorted_array.dat" using 1:7 with linespoints title "Unsorted Array", \
    "sorted_array.dat" using 1:7 with linespoints title "Sorted Array", \
    "singly_unsorted.dat" using 1:7 with linespoints title "Singly Unsorted", \
    "singly_sorted.dat" using 1:7 with linespoints title "Singly Sorted", \
    "doubly_unsorted.dat" using 1:7 with linespoints title "Doubly Unsorted", \
    "doubly_sorted.dat" using 1:7 with linespoints title "Doubly Sorted"

# Successor
set output "successor.png"
set title "Successor Operation"
plot \
    "unsorted_array.dat" using 1:8 with linespoints title "Unsorted Array", \
    "sorted_array.dat" using 1:8 with linespoints title "Sorted Array", \
    "singly_unsorted.dat" using 1:8 with linespoints title "Singly Unsorted", \
    "singly_sorted.dat" using 1:8 with linespoints title "Singly Sorted", \
    "doubly_unsorted.dat" using 1:8 with linespoints title "Doubly Unsorted", \
    "doubly_sorted.dat" using 1:8 with linespoints title "Doubly Sorted"

unset output
