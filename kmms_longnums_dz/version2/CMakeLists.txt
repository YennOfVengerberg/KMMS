cmake_minimum_required(VERSION 4.2)

project(long_nums)

enable_testing()

set(library "long_nums_lib")
add_library(${library})

add_subdirectory(
    "${CMAKE_CURRENT_LIST_DIR}/../lib/googletest"
    "${CMAKE_BINARY_DIR}/googletest"
)

add_subdirectory(srcs)
add_subdirectory(tests)


set(CMAKE_SUPPRESS_REGENERATION true)