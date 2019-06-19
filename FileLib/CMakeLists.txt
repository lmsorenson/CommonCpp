cmake_minimum_required (VERSION 2.6)

project (Text)

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR} )

#create executable
#--------------------------
add_library(Text ${PROJECT_SOURCE_DIR}/src/main.cpp)

#link include directories
#--------------------------

include_directories()

#link static lib binaries
#--------------------------

target_link_libraries()
