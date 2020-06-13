#!/bin/bash

cd libraries/ParseLib/tests/cmake
cmake ..
cd CMakeFiles/TestComponents.dir/src/

pwd
ls
gcov-9 -version
gcov-9 TestComponents.gnco
lcov --capture --directory . --output-file PROJECT_NAME.info
genhtml PROJECT_NAME.info --output-directory CODE_COVERAGE