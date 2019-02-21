cmake_minimum_required(VERSION 3.9)

project(trayzy CXX)

set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "CMake debug suffix")

include_directories(
	include
)

set(TARGET ${CMAKE_PROJECT_NAME}-app)
set(SOURCES src/main.cpp)
set(HEADERS
	include/trayzy/Camera.h
	include/trayzy/Forward.h
	include/trayzy/Hittable.h
	include/trayzy/HittableList.h
	include/trayzy/Ray.h
	include/trayzy/Sphere.h
	include/trayzy/Vec3.h
)

add_executable(${TARGET} ${SOURCES} ${HEADERS})

install(
	TARGETS ${TARGET}
	DESTINATION ${CMAKE_BINARY_DIR}/bin
)

