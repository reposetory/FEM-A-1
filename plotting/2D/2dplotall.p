
FILES = system("ls -1 *.dat")
do for [data in FILES] {

set terminal gif animate delay 10
set xrange [-.5:6.5]
set yrange [-.5:6.5]

plotfile = "outplot".data.".gif"
set output plotfile

stats data
set key autotitle columnheader
N = int(STATS_blocks)-1
do for [ind=0:N] {

set view map
set size ratio 1
set object 1 rect from graph 0, graph 0 to graph 1, graph 1 back
set object 1 rect fc rgb "black" fillstyle solid 1.0
set title sprintf("Timestep = %d", ind) 

splot data index ind using 1:2:3 with points pointtype 5 pointsize 3 palette 

}

}

