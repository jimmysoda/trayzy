cmake_minimum_required(VERSION 3.9)

project(trayzy CXX)

set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "CMake debug suffix")

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

install(
	TARGETS ${CMAKE_PROJECT_NAME}
	DESTINATION ${CMAKE_BINARY_DIR}/bin
)

