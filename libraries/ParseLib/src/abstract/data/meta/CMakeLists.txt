cmake_minimum_required (VERSION 2.6)

if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(metadata)

message(${PROJECT_SOURCE_DIR})

file(
    GLOB modules
    ${PROJECT_SOURCE_DIR}/source/*.cpp
)

set(metadata_modules ${modules} PARENT_SCOPE)