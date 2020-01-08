# CMakeList.txt : CMake project for GameOfLife-cmake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(GameOfLife CXX)
# Add source to this project's executable.

set (SRC Field.cpp main.cpp)

add_executable (${PROJECT_NAME} ${SRC})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${SOLUTION_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${SOLUTION_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${SOLUTION_DIR}/bin"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${SOLUTION_DIR}/SFML/include ${SOLUTION_DIR}/GameOfLife)
target_link_directories(${PROJECT_NAME} PUBLIC ${SOLUTION_DIR}/lib)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)


if (CMAKE_BUILD_TYPE MATCHES "[rR]el")
	target_link_libraries(${PROJECT_NAME} sfml-main)
endif()
