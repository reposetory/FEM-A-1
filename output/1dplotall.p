
FILES = system("ls -1 *.dat") 
do for [data in FILES] { 

set terminal gif animate delay 10
set xrange [0:6.2] 
set yrange [-3:3]

plotfile = "outplot".data.".gif"  
set output plotfile  

stats data 
set key autotitle columnheader 
N = int(STATS_blocks)-1

do for [ind=0:N] {

set title sprintf("Timestep = %d", ind) 

plot data index ind using 1:2 with linespoint  


}

}
