add_executable(ppm_writer ppm_writer.cpp)
install(
	TARGETS
		ppm_writer
	DESTINATION
		${CMAKE_BINARY_DIR}/bin
)

