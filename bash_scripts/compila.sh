#!/bin/sh

if [ "$1" != "local" ]; then
  #SBATCH --output=compilado-%j.out
  . /etc/profile
  module avail
  module load gcc/12.1.0
fi

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
