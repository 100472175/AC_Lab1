#!/bin/sh

rm -rf build

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
echo "compilado!!"