cmake_minimum_required(VERSION 3.2...3.27.5)

project(kmms_prog_2023)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(recursion)
add_subdirectory(scl)
add_subdirectory(sortings)
add_subdirectory(travel_to_russia)

set(CMAKE_SUPPRESS_REGENERATION true)
