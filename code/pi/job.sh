#!/bin/bash

#PBS -N pi
#PBS -A ntnu603
#PBS -l walltime=00:01:00
#PBS -l select=2:ncpus=32:mpiprocs=16

module load mpt

cd $PBS_O_WORKDIR
mpiexec_mpt ./pi 1000000
