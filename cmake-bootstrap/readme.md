# CMake

**CMake 3.x is preferred.**

- [CMake](#cmake)
  - [Install CMake](#install-cmake)
  - [Learn by Examples](#learn-by-examples)
    - [Example-1: Multi-Libraries and Multi-Executables](#example-1-multi-libraries-and-multi-executables)
      - [Project Structure](#project-structure)
      - [Intro](#intro)
      - [CMakeLists.txt](#cmakeliststxt)

## Install CMake

On Ubuntu: `sudo apt install cmake`.

See [Installing CMake](https://cliutils.gitlab.io/modern-cmake/chapters/intro/installing.html) for more approaches.

## Learn by Examples

### Example-1: Multi-Libraries and Multi-Executables

#### Project Structure

(generated using `tree .`)
```
.
├── build
├── CMakeLists.txt
└── src
    ├── helpers
    │   ├── CMakeLists.txt
    │   ├── helper.cc
    │   └── helper.hh
    ├── main2.cc
    ├── main.cc
    └── utils
        ├── CMakeLists.txt
        ├── math_func.cc
        ├── math_func.hh
        ├── print_func.cc
        └── print_func.hh
```

In `build/`, run `cmake ..` to generate `Makefile` and then run `make` to build the project.

#### Intro

In the project root directory:

1. `mkdir src`, where we write all our source code;
2. `mkdir build`, where we generate all building files and executables;
3. `touch CMakeLists.txt`, which is our main configuration file.

We want to have the following three libraries:

1. `src/utils/math_func`, where we implement a simple `x+1` function;
2. `src/utils/print_func`, where we implement a `print_int` function;
3. `src/helpers/helper`, where we implement a `print x+1` function using `src/utils/math_func` and `src/utils/print_func`.

We also want to have two executables:

1. `src/main.cc`, where we will use `src/utils/math_func` and `src/utils/print_func`;
2. `src/main2.cc`, where we will use `src/helpers/helper`.

#### CMakeLists.txt

1. `CMakeLists.txt`

This is the main CMake configuration file:

```cmake
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
```

2. `src/utils/CMakeLists.txt`

```cmake
# build library
add_library (math_func math_func.hh math_func.cc)
add_library (print_func print_func.hh print_func.cc)
```

3. `src/helpers/CMakeLists.txt`

```cmake
# save all source files to variable `DIR_LIB_SRCS`
aux_source_directory(. DIR_LIB_SRCS)

# build library from all source files
add_library (helper ${DIR_LIB_SRCS})
```
