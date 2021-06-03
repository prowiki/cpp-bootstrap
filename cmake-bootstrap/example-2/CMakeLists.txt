cmake_minimum_required(VERSION 3.13)

project(template__study)

set(CMAKE_CXX_STANDARD 17)

SET (CMAKE_VERBOSE_MAKEFILE 1)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "boost_1_76_0/")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "boost_1_76_0/libs")

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.76.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(use_boost src/use_boost.cc) 
    target_link_libraries(use_boost ${Boost_LIBRARIES} rt)
endif()
