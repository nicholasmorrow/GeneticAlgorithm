cmake_minimum_required (VERSION 2.8.11)
project (GeneticAlgorithm)
set(LIBRARY_NAME GeneticAlgorithm)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../bin/)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-std=c++11)
add_library (GeneticAlgorithm SHARED GeneticAlgorithm.cpp)
add_executable (Test test.cpp)
target_link_libraries (Test GeneticAlgorithm)
