#!/bin/bash

# Request an hour of runtime:
#SBATCH -t 00:10:00

#SBATCH --partition=batch
#SBATCH --ntasks-per-node=3
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

cd QT
qmake -project
qmake
make
./QT


cd ..
mpirun -n 3 ./main
#./main


# end time
T_END=$(date +%s)
# walltime
T_WALL=$(expr ${T_END} - ${T_START})
echo "walltime=${T_WALL}s"
