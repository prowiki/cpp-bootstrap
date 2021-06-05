# set the minimum cmake version
cmake_minimum_required(VERSION 3.13)

# set project name
project(cmake_study)

# set cpp standard
set(CMAKE_CXX_STANDARD 17)

# include dir, then we can use `#include "relative-header-path-to-src"` in any dir 
include_directories(src/)
include_directories(externals/catch2/)

# specify sub-dir to build, where we should also write a `CMakeLists.txt`
add_subdirectory(src/common_utils)
add_subdirectory(tests/common_utils)
add_subdirectory(externals/catch2)

# add tests
# run `ctest` to run the added tests; run with `--output-on-failure` to output failures
include(CTest)
add_test(NAME TestCommonUtils COMMAND test_common_utils)
