cmake_minimum_required(VERSION 3.20)
project(map_reduce_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(map_reduce_lib STATIC map_reduce.cpp operations.cpp)