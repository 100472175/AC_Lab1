#!/bin/sh

. /etc/profile
module avail
module load gcc/12.1.0
echo "*** BASE ***"
perf stat -r 5build/fluid/fluid 1000 fluid-2023/in/large.fld kk.fld
perf stat -r 5 -a -e 'power/energy-cores/, power/energy-gpu/, power/energy-pkg/, power/energy-ram/' build/fluid/fluid 1000 fluid-2023/in/large.fld kk.fld

echo "*** Comprobación ***"
build/fluid/fluid 5 fluid-2023/in/large.fld 5.fld
echo "*** Ejecución correcta si no hay nada debajo ***"
diff 5.fld out/large-5.fld