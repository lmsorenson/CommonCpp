cmake_minimum_required (VERSION 2.6)

project(SemanticAnalyzerComponent)

file( 
    GLOB Mods
    ${PROJECT_SOURCE_DIR}/private/source/*.cpp
    )

add_library(analyzer ${Mods})