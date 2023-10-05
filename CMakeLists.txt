cmake_minimum_required(VERSION 3.26)
project(AC3)

set(CMAKE_CXX_STANDARD 20)

add_executable(AC3
    sim/block.hpp
    sim/block.cpp
    sim/grid.hpp
    sim/grid.cpp
    sim/progargs.hpp
    sim/progargs.cpp
    fluid/fluid.cpp
    sim/calculos.cpp
    sim/calculos.hpp
    sim/file.cpp
    sim/file.hpp
)
