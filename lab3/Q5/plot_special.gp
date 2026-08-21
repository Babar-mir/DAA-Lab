set title "specialMultiply(): Time vs Input Size (log-log)"
set xlabel "Input Size n"
set ylabel "Time (microseconds)"
set logscale xy
set grid
set key top left
set terminal pngcairo size 900,600 enhanced font "Arial,11"
set output "special_complexity.png"

# scale factor chosen so the n^2 reference curve overlays near the data
scale = 0.35

plot "timing_data.txt" using 1:2 with linespoints lw 2 pt 7 lc rgb "purple" title "Measured time", \
     "timing_data.txt" using 1:(scale*($1**2)) with lines lw 2 dt 2 lc rgb "gray" title "Reference O(n^2) curve"
