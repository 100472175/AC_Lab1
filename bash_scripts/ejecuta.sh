#!/bin/sh

. /etc/profile
module avail
module load gcc/12.1.0
echo "*** BASE ***"
perf stat  build/fluid/fluid 1000 fluid-2023/in/large.fld out-base.fld
