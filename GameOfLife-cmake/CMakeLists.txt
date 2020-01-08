# CMakeList.txt : CMake project for GameOfLife-cmake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(GameOfLife CXX)
# Add source to this project's executable.

set (SRC Field.cpp main.cpp)

add_executable (${PROJECT_NAME} ${SRC})


# TODO: Add tests and install targets if needed.
