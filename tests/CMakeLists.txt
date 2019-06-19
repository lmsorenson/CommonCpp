# cmake_minimum_required (VERSION 2.6)

project (tests)

set (CMAKE_CXX_STANDARD 11)

add_subdirectory(
	${PROJECT_SOURCE_DIR}/../submodules/googletest/googletest 
	lib/
)

set( 
	EXECUTABLE_OUTPUT_PATH 
	${PROJECT_SOURCE_DIR}/out/
)

add_executable(tests ${PROJECT_SOURCE_DIR}/src/TestsMain.cpp)

target_link_libraries(
	tests
	gtest
	# ${PROJECT_SOURCE_DIR}/local/lib/libgtest.a
)


include_directories(
	tests
	${PROJECT_SOURCE_DIR}/../submodules/googletest/googletest/include
	# ${PROJECT_SOURCE_DIR}/local/include/
)
