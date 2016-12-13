#!/bin/bash

# Request an hour of runtime:
#SBATCH -t 00:30:00

#SBATCH --partition=batch
#SBATCH --ntasks-per-node=6
#SBATCH --mem-per-cpu=10G
#SBATCH --constraint="e5-2670"

# start time
T_START=$(date +%s)

# Specify a job name:
#SBATCH -J run
# Specify an output file
#SBATCH -o Job%j.out
# Specify an error file
#SBATCH -e Job%j.err

# Run a command
module load mpich
module load gcc
module load qt
module load cmake
module unload gnuplot

cmake CMakeLists.txt
make

cd QT
qmake -project
qmake
make
./QT

threads=$(<num_threads.txt)
echo "$threads"
cd ..
mpirun -n $threads ./main
#./main

cd output/1Doutput
gnuplot> load '1dplotall.p'
cd ../2Doutput
gnuplot> load '2dplotall.p'
cd ../..

# end time
T_END=$(date +%s)
# walltime
T_WALL=$(expr ${T_END} - ${T_START})
echo "walltime=${T_WALL}s"
