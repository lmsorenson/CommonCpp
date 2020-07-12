#!/bin/bash

cd libraries/ParseLib/tests/cmake

cmake ..
../TestComponents

cd CMakeFiles/TestComponents.dir/src/

pwd
ls
gcov -version
gcov -o coverage.xml TestComponents.gnco 
lcov --capture --directory . --output-file ParseLibComponents.info
genhtml ParseLibComponents.info --output-directory CoverageReport
cd CoverageReport/
open index.html