cmake_minimum_required (VERSION 2.6)

project(ParserComponent)

file( 
    GLOB Mods
    ${PROJECT_SOURCE_DIR}/public/source/*.cpp
    ${PROJECT_SOURCE_DIR}/private/*.cpp
    ${PROJECT_SOURCE_DIR}/private/queue/source/*.cpp
    ${PROJECT_SOURCE_DIR}/private/sequence/source/*.cpp
    ${PROJECT_SOURCE_DIR}/private/shape/source/*.cpp
    )

add_library(parser ${Mods})