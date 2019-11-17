#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.h>

#include "CSVFormatSpecTests.hpp"
#include "CSVFunctionalTests.hpp"
// #include "CSVPerformanceTests.hpp"

using namespace std;

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    std::string path = argv[0];
    size_t position = path.find_last_of("/");
    if(position!=string::npos)
        LucTestFramework::SetPath(path.substr(0, position+1));

	return RUN_ALL_TESTS();
}