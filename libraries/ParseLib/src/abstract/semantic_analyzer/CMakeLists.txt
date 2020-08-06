cmake_minimum_required (VERSION 2.6)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(SemanticAnalyzerComponent)

file( 
    GLOB Mods
    ${PROJECT_SOURCE_DIR}/private/*.cpp
    ${PROJECT_SOURCE_DIR}/private/net/source/*.cpp
    ${PROJECT_SOURCE_DIR}/private/queue/source/*.cpp
    )

add_library(analyzer ${Mods})