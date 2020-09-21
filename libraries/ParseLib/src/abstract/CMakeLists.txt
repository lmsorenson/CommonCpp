cmake_minimum_required (VERSION 2.6)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project (abstract)

add_subdirectory(${PROJECT_SOURCE_DIR}/lexer/ ${PROJECT_BINARY_DIR}/lexer/)
add_subdirectory(${PROJECT_SOURCE_DIR}/parser/ ${PROJECT_BINARY_DIR}/parser/)
add_subdirectory(${PROJECT_SOURCE_DIR}/semantic_analyzer/ ${PROJECT_BINARY_DIR}/semantic_analyzer/)
add_subdirectory(${PROJECT_SOURCE_DIR}/data/ ${PROJECT_BINARY_DIR}/data/)

