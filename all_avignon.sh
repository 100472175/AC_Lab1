#!/bin/sh
sbatch cmake.sh
sleep 2
sbatch make.sh
sleep 2
job_id_fluid=$(sbatch fluid.sh | awk '{print $4}')
echo "Submitted batch job $job_id_fluid"
sleep 3
tail -f slurm-$job_id_fluid.out &
sbatch fluid.sh