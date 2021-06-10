cmake_minimum_required(VERSION 3.13)

project(variant_study)

SET (CMAKE_VERBOSE_MAKEFILE 1)

set(CMAKE_CXX_STANDARD 20)

add_executable(variant variant.cc)
add_executable(example example.cc)
