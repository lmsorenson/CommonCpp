cmake_minimum_required (VERSION 2.6)

project (parse)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "-g")
# set (CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR} )

option(ENABLE_DEBUG "Set to ON to enable ParseLib debug features" ON)

#create a lib
#--------------------------
file( 
    GLOB Mods 
    ${PROJECT_SOURCE_DIR}/*.cpp 
    ${PROJECT_SOURCE_DIR}/abstract/Factories/*.cpp
    ${PROJECT_SOURCE_DIR}/abstract/data/*.cpp
    ${PROJECT_SOURCE_DIR}/abstract/data/dataset/*.cpp
    ${PROJECT_SOURCE_DIR}/abstract/data/instance/*.cpp
    ${PROJECT_SOURCE_DIR}/abstract/data/keys/source/*.cpp
    ${PROJECT_SOURCE_DIR}/abstract/data/meta/source/*.cpp
    ${PROJECT_SOURCE_DIR}/abstract/data/structures/source/*.cpp
    ${PROJECT_SOURCE_DIR}/abstract/Reads/*.cpp
    ${PROJECT_SOURCE_DIR}/abstract/Writes/*.cpp
    ${PROJECT_SOURCE_DIR}/concrete/csv/*.cpp
    ${PROJECT_SOURCE_DIR}/utils/source/*.cpp
    )

add_library(parse ${Mods})

if(ENABLE_DEBUG)

file( 
    GLOB parse_includes
    ${PROJECT_SOURCE_DIR}/../include/*.h
    ${PROJECT_SOURCE_DIR}/../include/*.hpp
    ${PROJECT_SOURCE_DIR}/../include/concrete/*.hpp
    )
endif()

