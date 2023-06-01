cmake_minimum_required(VERSION 3.22)
project(map_reduce_tests)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(map_reduce_tests test_map_reduce.cpp)
include_directories(../src)

target_link_libraries(map_reduce_tests map_reduce_lib)
target_link_libraries(map_reduce_tests gtest gtest_main)

add_test(NAME map_reduce_tests
        COMMAND map_reduce_tests)

find_program(VALGRIND valgrind)
if (VALGRIND)
    add_custom_target(valgrind
            COMMAND "${VALGRIND}" --tool=memcheck --leak-check=yes
            --show-reachable=yes --num-callers=20 --track-fds=yes $<TARGET_FILE:map_reduce_tests>)
endif()
