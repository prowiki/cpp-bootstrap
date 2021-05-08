cmake_minimum_required(VERSION 3.13)

project(pointer_study)

set(CMAKE_CXX_STANDARD 17)

add_executable(basic basic.cc)
add_executable(mem mem.cc)
add_executable(smart smart.cc)
