#!/bin/bash

cd libraries/ParseLib/tests/cmake
cmake ..
cd CMakeFiles/TestComponents.dir/src/

pwd
ls
gcov -version
gcov TestComponents.gnco
lcov --capture --directory . --output-file PROJECT_NAME.info
genhtml PROJECT_NAME.info --output-directory CODE_COVERAGE
cd CODE_COVERAGE/
open index.html