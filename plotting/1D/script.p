# gnuplot plotting
# run with gnuplot> load 'scriptname.p'

set autoscale
unset log
unset label
set xtic auto
set ytic auto
set title "values at positions at time = _ "
set xlabel "position"
set ylabel "value"
#set key 0,10
#set label "labelname" at 2.0,2.0
#set arrow from 2.3,4.9 to 8,9
set xr [0.0:7]
set yr [-2:2]

#plot "tvalues" using 1:2 title 'dataA', \"fileB.dat" using 1:3 title 'data B'


plot 'xycol' using 1:2 with linespoint title 'values'

#       set multiplot;                          # get into multiplot mode
#      set size 1,0.5;  
#      set origin 0.0,0.5;   plot sin(x); 
#      set origin 0.0,0.0;   plot cos(x)
#      unset multiplot                         # exit multiplot mode


