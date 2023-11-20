#!/bin/zsh
cd ../..
echo "Compilando"
# If build does not exist, create it
if [ ! -d "build" ]; then
    mkdir build
fi
. /etc/profile
module avail
module load gcc/12.1.0
cmake --version
time cmake -S fluid-2023 -B build -DCMAKE_BUILD_TYPE=Release
time cmake --build build -j
# shellcheck disable=SC2103
cd ..
echo "Probando trazas pequeñas"
./build/fluid/fluid 1 small.fld small-1.fld > /dev/null
diff small-1.fld out/small-1.fld
echo "*********Compromación small 1 correcta*********"
./build/fluid/fluid 2 small.fld small-2.fld > /dev/null
diff small-2.fld out/small-2.fld
echo "*********Compromación small 2 correcta*********"
./build/fluid/fluid 3 small.fld small-3.fld > /dev/null
diff small-3.fld out/small-3.fld
echo "*********Compromación small 3 correcta*********"
./build/fluid/fluid 4 small.fld small-4.fld > /dev/null
diff small-4.fld out/small-4.fld
echo "*********Compromación small 4 correcta*********"
./build/fluid/fluid 5 small.fld small-5.fld > /dev/null
diff small-5.fld out/small-5.fld
echo "*********Compromación small 5 correcta*********"
echo "%%%%% Compromación small %%%%%"
echo "%%% Probando trazas grandes%%%"
./build/fluid/fluid 1 large.fld large-1.fld > /dev/null
diff large-1.fld out/large-1.fld
echo "*********Compromación large 1 correcta*********"
./build/fluid/fluid 2 large.fld large-2.fld > /dev/null
diff large-2.fld out/large-2.fld
echo "*********Compromación large 2 correcta*********"
./build/fluid/fluid 3 large.fld large-3.fld > /dev/null
diff large-3.fld out/large-3.fld
echo "*********Compromación large 3 correcta*********"
./build/fluid/fluid 4 large.fld large-4.fld > /dev/null
diff large-4.fld out/large-4.fld
echo "*********Compromación large 4 correcta*********"
./build/fluid/fluid 5 large.fld large-5.fld > /dev/null
diff large-5.fld out/large-5.fld
echo "*********Compromación large 5 correcta*********"
echo "Fin de las pruebas"