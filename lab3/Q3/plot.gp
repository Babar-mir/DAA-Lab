set title "Divide-and-Conquer Max-Min Comparisons"
set xlabel "Input Size (n)"
set ylabel "Number of Comparisons"
set grid

plot "max_min_comparisons.dat" using 1:2 with linespoints title "Actual Comparisons", \
     "max_min_comparisons.dat" using 1:3 with linespoints title "3n/2 Bound"