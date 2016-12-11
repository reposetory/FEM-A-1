
FILES = system("ls -1 *.dat")
do for [data in FILES] {

set terminal gif animate delay 10
set xrange [0:6.2]
set yrange [-3:3]

plotfile = "outplot".data.".gif"
set output plotfile

# set output 'heatmap.png'
set view map
set size ratio 1
set object 1 rect from graph 0, graph 0 to graph 1, graph 1 back
set object 1 rect fc rgb "black" fillstyle solid 1.0

stats data
set key autotitle columnheader
N = int(STATS_blocks)-1
do for [ind=0:N] {
set title "Timestep = %d", ind) 

splot data using 1:2:3 with points pointtype 5 pointsize 1 palette 

}

}

