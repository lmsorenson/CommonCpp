cmake_minimum_required (VERSION 2.6)

project (abstract)

add_subdirectory(${PROJECT_SOURCE_DIR}/lexer/ ${PROJECT_BINARY_DIR})
add_subdirectory(${PROJECT_SOURCE_DIR}/parser/ ${PROJECT_BINARY_DIR})
add_subdirectory(${PROJECT_SOURCE_DIR}/semantic_analyzer/ ${PROJECT_BINARY_DIR})