cmake_minimum_required(VERSION 4.2)

project(long_nums)

enable_testing()

set(library "long_nums_lib")
add_library(${library})

add_subdirectory(lib/googletest)

add_subdirectory(tests)
add_subdirectory(srcs)

set(CMAKE_SUPPRESS_REGENERATION true)