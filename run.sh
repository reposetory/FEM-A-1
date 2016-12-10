#!/bin/bash

# Request an hour of runtime:
#SBATCH -t 1:00:00

#SBATCH --partition=batch
#SBATCH --ntasks-per-node=1
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

cd QT
./QT
cp parameters.txt ../ 

cd ..
mpirun -n 1 ./main


# end time
T_END=$(date +%s)
# walltime
T_WALL=$(expr ${T_END} - ${T_START})
echo "walltime=${T_WALL}s"
