# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (GameOfLife)

set(SOLUTION_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTION_OUTPUT_PATH ${SOLUTION_DIR}/bin)

# Include sub-projects.
add_subdirectory(SFML)
add_subdirectory (GameOfLife)
