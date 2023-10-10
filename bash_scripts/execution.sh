#!/bin/sh
echo "Ejecución..."
echo "Ejecución: 1 iteración:"
./build/fluid/fluid 1 small.fld out_1it.fld
echo "***====================***"
echo "Ejecución: 10 iteraciones:"
./build/fluid/fluid 10 small.fld out_10it.fld
echo "***====================***"
echo "Ejecución: 100 iteraciones:"
./build/fluid/fluid 100 small.fld out_100it.fld
