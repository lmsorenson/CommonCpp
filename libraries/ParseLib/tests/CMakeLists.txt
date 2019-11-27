cmake_minimum_required (VERSION 2.6)

project (tests)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "-g")
# set (CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)


include_directories(${PROJECT_SOURCE_DIR}/../include/)

add_subdirectory(
	${PROJECT_SOURCE_DIR}/../src/
	lib/
)

include_directories(
	tests
	${PROJECT_SOURCE_DIR}/../../../submodules/googletest/googletest/include
)
add_subdirectory(
	${PROJECT_SOURCE_DIR}/../../../submodules/googletest/googletest 
	lib/
)

set( 
	EXECUTABLE_OUTPUT_PATH 
	${PROJECT_SOURCE_DIR}/out/
)

add_executable(tests ${PROJECT_SOURCE_DIR}/src/TestsMain.cpp)

target_include_directories(
	tests PUBLIC
	${PROJECT_SOURCE_DIR}/../src/include
	${PROJECT_SOURCE_DIR}/../src/
	${PROJECT_SOURCE_DIR}/../src/abstract/Factories/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/meta/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/structures/
    ${PROJECT_SOURCE_DIR}/../src/abstract/Reads/
    ${PROJECT_SOURCE_DIR}/../src/abstract/Writes/
    ${PROJECT_SOURCE_DIR}/../src/concrete/csv/
)

target_link_libraries(
	tests
	gtest
	parse
)



