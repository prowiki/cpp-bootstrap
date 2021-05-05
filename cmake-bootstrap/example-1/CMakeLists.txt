# set the minimum cmake version
cmake_minimum_required(VERSION 3.13)

# set project name
project(cmake_study)

# set cpp standard
set(CMAKE_CXX_STANDARD 17)

# include dir, then we can use `#include "relative-header-path-to-src"` in any dir 
include_directories(src/)

# specify sub-dir to build, where we should also write a `CMakeLists.txt`
add_subdirectory(src/utils)

# build an executable
add_executable(cmake_study src/main.cc)

# link math_func and print_func static libraries to cmake_study executable
target_link_libraries(cmake_study math_func print_func)

# specify sub-dir to build, where we should also write a `CMakeLists.txt`
add_subdirectory(src/helpers)

# build an executable
add_executable(cmake_study2 src/main2.cc)

# link static libraries to cmake_study executable
# one thing to note is that we also need to link math_func and print_func
# though we only include `helpers/helper.hh` in `src/main2.cc`
target_link_libraries(cmake_study2 helper math_func print_func)