cmake_minimum_required (VERSION 2.6)

if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(data)

message(${PROJECT_SOURCE_DIR})

add_subdirectory(${PROJECT_SOURCE_DIR}/meta/ ${PROJECT_BINARY_DIR}/metadata/)

add_library(data-core ${metadata_modules})