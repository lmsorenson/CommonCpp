cmake_minimum_required (VERSION 2.6)

project (Filum)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set (CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR} )

#create a lib
#--------------------------
file( 
    GLOB Mods 
    ${PROJECT_SOURCE_DIR}/*.cpp 
    ${PROJECT_SOURCE_DIR}/Factories/*.cpp
    ${PROJECT_SOURCE_DIR}/DataStructures/*.cpp
    ${PROJECT_SOURCE_DIR}/Reads/*.cpp
    ${PROJECT_SOURCE_DIR}/Writes/*.cpp
    )

add_library(Filum ${Mods})

