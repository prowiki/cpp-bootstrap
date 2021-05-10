cmake_minimum_required(VERSION 3.13)

project(forward_declaration_study)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/)

add_subdirectory(src/helpers)
add_subdirectory(src/objects)

add_executable(main src/main.cc)

target_link_libraries(main book_helper)
