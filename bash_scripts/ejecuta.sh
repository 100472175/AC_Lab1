#!/bin/sh

if [ "$3" != "local" ]; then
  #SBATCH --output=salida-%j.out
  . /etc/profile
  module avail
  module load gcc/12.1.0
fi

echo "*** BASE ***"
perf stat -r $1 -a -e 'task-clock,context-switches,cpu-migrations,page-faults,cycles,instructions,branches,branch-misses,cache-references,cache-misses,power/energy-cores/, power/energy-gpu/, power/energy-pkg/, power/energy-ram/' build/fluid/fluid $2 fluid-2023/large.fld kk.fld