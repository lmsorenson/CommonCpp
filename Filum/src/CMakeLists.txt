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
    ${PROJECT_SOURCE_DIR}/abstract/Factories/*.cpp
    ${PROJECT_SOURCE_DIR}/abstract/DataStructures/*.cpp
    ${PROJECT_SOURCE_DIR}/abstract/Reads/*.cpp
    ${PROJECT_SOURCE_DIR}/abstract/Writes/*.cpp
    ${PROJECT_SOURCE_DIR}/concrete/csv/*.cpp
    )

add_library(Filum ${Mods})

