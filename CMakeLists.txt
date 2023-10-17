cmake_minimum_required(VERSION 3.26)
project(AC3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
#set(CMAKE_CXX_CLANG_TIDY clang-tidy -header-filter=.∗)
include_directories (PUBLIC .)
add_subdirectory(sim)
add_subdirectory(fluid)
