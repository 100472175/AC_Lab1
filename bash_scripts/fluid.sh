#!/bin/sh
cd ../build_avignon
time ./fluid/fluid 1 ../small.fld ../out_small.out
diff ../small.fld ../out_small.out