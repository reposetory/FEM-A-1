
set title "3D surface "
set xrange [0:7]
set yrange [0:7]



# set output 'heatmap.png'
set view map
set size ratio 1
set object 1 rect from graph 0, graph 0 to graph 1, graph 1 back
set object 1 rect fc rgb "black" fillstyle solid 1.0

set title "Heat Map generated by 'plot' from XYZ values" 
## Last datafile plotted: "$map2"



splot 'aa.dat' using 1:2:3 with points pointtype 5 pointsize 1 palette 

