#!/bin/sh

. /etc/profile
module avail
module load gcc/12.1.0
cmake --version
time cmake -S fluid-2023 -B build -DCMAKE_BUILD_TYPE=Release
time cmake --build build
