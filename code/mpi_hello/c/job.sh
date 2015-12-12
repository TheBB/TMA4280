#!/bin/bash

#PBS -N hello
#PBS -A ntnu603
#PBS -l walltime=00:01:00
#PBS -l select=1:ncpus=32:mpiprocs=16

module load mpt

cd $PBS_O_WORKDIR
mpiexec_mpt ./hello
