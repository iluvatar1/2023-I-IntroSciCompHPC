#!/bin/bash -l
#SBATCH --job-name="bandwith"
# #SBATCH --account="HerrComp" # not used
#SBATCH --mail-type=ALL
#SBATCH --mail-user=wfoquendop@unal.edu.co
#SBATCH --time=01:00:00
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=6
#SBATCH --partition=12threads

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

#srun hostname
pwd
#srun --mpi=list
#mpirun -np 2 ./a.out 5 10000000
srun --mpi=pmix ./a.out 5 10000000

