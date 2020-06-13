cmake_minimum_required (VERSION 2.6)

project (tests)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set (CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
set (CMAKE_C_FLAGS "-g")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)



include_directories(${PROJECT_SOURCE_DIR}/../include/)

add_subdirectory(
	${PROJECT_SOURCE_DIR}/../src/
	lib/
)

include_directories(
	tests
	${PROJECT_SOURCE_DIR}/../../../submodules/googletest/googletest/include
	${PROJECT_SOURCE_DIR}/../../../submodules/googletest/googletest/include/concrete
)


add_subdirectory(
	${PROJECT_SOURCE_DIR}/../../../submodules/googletest/googletest 
	lib/
)

set( 
	EXECUTABLE_OUTPUT_PATH 
	${PROJECT_SOURCE_DIR}
)

add_executable(TestAll 
	${PROJECT_SOURCE_DIR}/src/TestAll.cpp
	${PROJECT_SOURCE_DIR}/src/ComponentTests/LexerComponent/test_lexer_filters.cpp)
add_executable(TestComponents 
	${PROJECT_SOURCE_DIR}/src/TestComponents.cpp
	${PROJECT_SOURCE_DIR}/src/ComponentTests/LexerComponent/test_lexer_filters.cpp)
add_executable(TestIntegration ${PROJECT_SOURCE_DIR}/src/TestIntegration.cpp)
add_executable(TestSystem ${PROJECT_SOURCE_DIR}/src/TestSystem.cpp)

target_include_directories(
	TestAll PUBLIC 
	${PROJECT_SOURCE_DIR}/../include/
	${PROJECT_SOURCE_DIR}/../include/concrete
	${PROJECT_SOURCE_DIR}/../src/abstract/Factories/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/meta/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/structures/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/instance/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/dataset/
	${PROJECT_SOURCE_DIR}/../src/abstract/Reads/
	${PROJECT_SOURCE_DIR}/../src/abstract/Writes/
	${PROJECT_SOURCE_DIR}/../src/concrete/csv/
	${PROJECT_SOURCE_DIR}/../src/utils/
	${PROJECT_SOURCE_DIR}/../src/utils/source
)

target_include_directories(
	TestComponents PUBLIC 
	${PROJECT_SOURCE_DIR}/../include/
	${PROJECT_SOURCE_DIR}/../include/concrete
	${PROJECT_SOURCE_DIR}/../src/abstract/Factories/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/meta/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/structures/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/instance/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/dataset/
	${PROJECT_SOURCE_DIR}/../src/abstract/Reads/
	${PROJECT_SOURCE_DIR}/../src/abstract/Writes/
	${PROJECT_SOURCE_DIR}/../src/concrete/csv/
	${PROJECT_SOURCE_DIR}/../src/utils/
	${PROJECT_SOURCE_DIR}/../src/utils/source
)

target_include_directories(
	TestIntegration PUBLIC 
	${PROJECT_SOURCE_DIR}/../include/
	${PROJECT_SOURCE_DIR}/../include/concrete
	${PROJECT_SOURCE_DIR}/../src/abstract/Factories/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/meta/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/structures/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/instance/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/dataset/
	${PROJECT_SOURCE_DIR}/../src/abstract/Reads/
	${PROJECT_SOURCE_DIR}/../src/abstract/Writes/
	${PROJECT_SOURCE_DIR}/../src/concrete/csv/
	${PROJECT_SOURCE_DIR}/../src/utils/
	${PROJECT_SOURCE_DIR}/../src/utils/source
)

target_include_directories(
	TestSystem PUBLIC 
	${PROJECT_SOURCE_DIR}/../include/
	${PROJECT_SOURCE_DIR}/../include/concrete
	${PROJECT_SOURCE_DIR}/../src/abstract/Factories/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/meta/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/structures/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/instance/
	${PROJECT_SOURCE_DIR}/../src/abstract/data/dataset/
	${PROJECT_SOURCE_DIR}/../src/abstract/Reads/
	${PROJECT_SOURCE_DIR}/../src/abstract/Writes/
	${PROJECT_SOURCE_DIR}/../src/concrete/csv/
	${PROJECT_SOURCE_DIR}/../src/utils/
	${PROJECT_SOURCE_DIR}/../src/utils/source
)

target_link_libraries(
	TestAll
	gtest
	parse
)

target_link_libraries(
	TestComponents
	gtest
	parse
)

target_link_libraries(
	TestIntegration
	gtest
	parse
)

target_link_libraries(
	TestSystem
	gtest
	parse
)