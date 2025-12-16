cmake_minimum_required(VERSION 4.2)

project(kmms_dz4)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(test)
add_subdirectory(menu)
add_subdirectory(sort)

set(CMAKE_SUPPRESS_REGENERATION true)