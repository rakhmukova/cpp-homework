cmake_minimum_required(VERSION 3.22)
project(map_reduce)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OpenMP found")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    message("OpenMP not found")
endif()

add_subdirectory(src)
add_subdirectory(tests)
