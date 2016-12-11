
set terminal gif animate delay 10 
set output 'gifsample1D.gif' 
set key autotitle columnheader
stats 'sample1d.dat'# nooutput 
set xrange [0:6.2] 
set yrange [-3:3]

#do for [i=1:int(STATS_blocks)] {
   #plot 'sample1d.dat' index i+1  using 1:2 with linespoint 
   #(this compiles)# plot 'sample1d.dat' using 1:2 with linespoint  

#}
#set key autotitle columnheader
N = int(STATS_blocks)-1

do for [ind=0:N] {
  #stats 'sample1d.dat' every ::i::i nooutput
  #a = STATS_min_x
  #b = STATS_min_y
#indtitle = 'times.dat' every ::i::i 
#set key autotitle columnheader 
set title sprintf("Timestep = %d", ind) 

plot 'sample1d.dat' index ind using 1:2 with linespoint  


}
