#!/bin/bash

#SBATCH -t 00:05:00 
#SBATCH --partition=batch
#SBATCH --ntasks-per-node=1
#SBATCH --constraint="e5-2670"
#SBATCH -o job%j.out 


gnuplot -p << eof
plot for [ file in "$@" ] file w 1
eof


