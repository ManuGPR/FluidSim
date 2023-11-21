#!/bin/sh

. /etc/profile
module avail
module load gcc/12.1.0
cmake -S . -B arq-release -DCMAKE_BUILD_TYPE=Release
#cmake -S fluid -B arq-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build arq-release -j
#cmake --build arq-debug
