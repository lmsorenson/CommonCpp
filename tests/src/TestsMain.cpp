#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.h>
// #include <abstract/Reads/ParserPipeline.hpp>

#include "CSVFunctionalTests.hpp"
#include "CSVPerformanceTests.hpp"

using namespace std;


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}