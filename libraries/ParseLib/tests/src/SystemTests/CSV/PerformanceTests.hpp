#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "../../TestFramework.hpp"



class CSVPerformanceSpec : public ::LucTestFramework
{
protected:
    
    CSVPerformanceSpec() {
    }
    
    virtual ~CSVPerformanceSpec() {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    
    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
    
    // Objects declared here can be used by all tests in the test case for Foo.
};

TEST_F(CSVPerformanceSpec, ten_thousand_line)
{
    std::clock_t start;
    double duration;

    start = std::clock();

    DataSet ds;

    ParseLib().read_file(ds, this->path("test_data/test2.csv").c_str());

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "Time elapsed: " << duration * 1000 << "ms" << std::endl;

    ASSERT_LT(duration * 1000, 16);
}