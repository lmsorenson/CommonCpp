cmake_minimum_required (VERSION 2.6)

project(LexerComponent)

file( 
    GLOB Mods
    ${PROJECT_SOURCE_DIR}/private/*.cpp
    ${PROJECT_SOURCE_DIR}/private/queue/source/*.cpp
    ${PROJECT_SOURCE_DIR}/private/shape/source/*.cpp
    ${PROJECT_SOURCE_DIR}/private/shape/dependent_entity/source/*.cpp
    )

add_library(lexer ${Mods})