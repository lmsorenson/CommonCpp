#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.h>


class CSVFunctionalSpec : public ::testing::Test
{
protected:
    
    CSVFunctionalSpec() {
    }
    
    virtual ~CSVFunctionalSpec() {
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

TEST_F(CSVFunctionalSpec, TestR1)
{
    AbstractDataStructure ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/test1.csv");

    string str = ds.get("R0F0");

    ASSERT_EQ(str, "January");
}

TEST_F(CSVFunctionalSpec, TestR2)
{

    ASSERT_EQ(true, false);
}

TEST_F(CSVFunctionalSpec, TestR4)
{
    AbstractDataStructure ds;
    
    int32_t exit_code = ParseLib().read_file(ds, "Invalid-Path");
    
    ASSERT_EQ(exit_code, 1);
}

TEST_F(CSVFunctionalSpec, TestR5)
{
    ASSERT_EQ(true, false);
}

TEST_F(CSVFunctionalSpec, TestR6)
{
    ASSERT_EQ(true, false);
}

TEST_F(CSVFunctionalSpec, TestR7)
{
    AbstractDataStructure ds;
    
    int32_t exit_code = ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/test1.csv");
    
    string str = ds.get("R100000F0");
    

    ASSERT_EQ(str, "ERROR");
}