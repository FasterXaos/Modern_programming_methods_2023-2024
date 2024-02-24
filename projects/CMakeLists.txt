cmake_minimum_required(VERSION 3.2...3.27.5)

project(kmms_prog_2023)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(radix_sort)
add_subdirectory(radix_sort_mf)
add_subdirectory(travel_to_russia)
add_subdirectory(unit_test_example)

set(CMAKE_SUPPRESS_REGENERATION true)
