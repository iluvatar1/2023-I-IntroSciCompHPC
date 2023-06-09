#!/bin/bash -l
#SBATCH --job-name="testmulti"
# #SBATCH --account="HerrComp" # not used
#SBATCH --mail-type=ALL
#SBATCH --mail-user=wfoquendop@unal.edu.co
#SBATCH --time=01:00:00
#SBATCH --nodes=3
#SBATCH --ntasks-per-node=2
#SBATCH --cpus-per-task=4
#SBATCH --partition=12threads

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

#srun hostname
srun stress -t 20 -c 4
