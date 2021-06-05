# CMake

**CMake 3.x is preferred.**

- [CMake](#cmake)
  - [Install CMake](#install-cmake)
  - [Learn by Examples](#learn-by-examples)
    - [Example-1: Multi-Libraries and Multi-Executables](#example-1-multi-libraries-and-multi-executables)
      - [Project Structure](#project-structure)
      - [Intro](#intro)
      - [CMakeLists.txt](#cmakeliststxt)
    - [Example-2: Use external libraries](#example-2-use-external-libraries)
      - [Project Structure](#project-structure-1)
      - [CMakeLists.txt](#cmakeliststxt-1)
    - [Example-3: Test with Catch2](#example-3-test-with-catch2)
      - [Project Structure](#project-structure-2)
      - [CMakeLists.txt](#cmakeliststxt-2)

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

CMake respects environment variables `CC` and `CXX` to determine which compilers will be used. By default, CMake can detect the compilers itself while running `cmake ..`. However, to specify the compilers, we can run e.g. `CXX=$(which clang++) cmake ..` to force it to use clang++. *ref*: [switching-between-gcc-and-clang-llvm-using-cmake](https://stackoverflow.com/questions/7031126/switching-between-gcc-and-clang-llvm-using-cmake)

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

### Example-2: Use external libraries

#### Project Structure

```
.
├── build
├── boost_1_76_0
├── CMakeLists.txt
└── src
    ├── use_boost.cc
```

1. [download boost](https://www.boost.org/users/download/) and extract it to get `boost_1_76_0`. In practice, we probably want to add boost as a submodule.
2. `use_boost.cc` is an inter-process shared memory example from [boost official docs](https://www.boost.org/doc/libs/1_49_0/doc/html/interprocess/sharedmemorybetweenprocesses.html).


#### CMakeLists.txt

1. `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.13)

project(template__study)

set(CMAKE_CXX_STANDARD 17)

# this shows the commands used to compile the code
SET (CMAKE_VERBOSE_MAKEFILE 1)

# add boost to the include-path and lib-path if it's not intalled
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "boost_1_76_0/")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "boost_1_76_0/libs")

# some boost flags
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# cmake has a command `find_package` can help find boost and set `Boost_FOUND`
find_package(Boost 1.76.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(use_boost src/use_boost.cc)
    target_link_libraries(use_boost ${Boost_LIBRARIES} rt)
endif()
```

Note `rt` in `target_link_libraries(use_boost ${Boost_LIBRARIES} rt)`. The link command is `/usr/bin/c++ CMakeFiles/use_boost.dir/src/use_boost.cc.o  -o use_boost  -lrt`. The `-lrt` means to link `librt`. *ref*: [what-library-does-ld-option-lrt-refer-to](https://stackoverflow.com/questions/6754032/what-library-does-ld-option-lrt-refer-to-bionic-libc). And the only reason why we need it is because the code is using some shared memory features.

### Example-3: Test with Catch2

#### Project Structure

```
.
├── CMakeLists.txt
├── build
├── externals
│   └── catch2
│       ├── CMakeLists.txt
│       └── catch.hpp
├── src
│   └── common_utils
│       ├── CMakeLists.txt
│       ├── math_utils.cc
│       └── math_utils.hh
└── tests
    └── common_utils
        ├── CMakeLists.txt
        ├── test_main.cc
        └── test_math_utils.cc
```

1. I'm using `Catch2` to help write tests. Download the header-only Catch2 from [Catch2 releases](https://github.com/catchorg/Catch2/releases).
2. In `externals/catch2`, I write a `CMakeLists.txt` to make catch2 an interface so that we can just link it to each of our `test-main`.
3. I only write a single lib `common_utils` and the corresponding test as an example, but we can add as many libs as we want.

#### CMakeLists.txt

I'm using `ctest` which should be installed with `cmake` to manage the tests.

```cmake
# add tests
# run `ctest` to run the added tests; run with `--output-on-failure` to output failures
include(CTest)
add_test(NAME TestCommonUtils COMMAND test_common_utils)
```
