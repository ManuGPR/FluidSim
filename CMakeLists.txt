cmake_minimum_required(VERSION 3.22)
project(AC3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
#set(CMAKE_CXX_CLANG_TIDY clang-tidy -header-filter=.∗)


# Enable GoogleTest Library
include(FetchContent)
FetchContent_Declare( googletest
                      GIT_REPOSITORY https://github.com/google/googletest.git
                      GIT_TAG v1.14.0)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


include_directories (PUBLIC .)
add_subdirectory(sim)
add_subdirectory(fluid)

enable_testing()
add_subdirectory(utest)