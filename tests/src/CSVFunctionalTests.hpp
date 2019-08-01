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
    AbstractDataStructure ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/test1.csv");


    //Test every value in the file.
    string 
    R0F0 = ds.get("R0F0"),
    R0F1 = ds.get("R0F1"),
    R1F0 = ds.get("R1F0"),
    R1F1 = ds.get("R1F1"), 
    R2F0 = ds.get("R2F0"),
    R2F1 = ds.get("R2F1"),
    R3F0 = ds.get("R3F0"),
    R3F1 = ds.get("R3F1"),
    R4F0 = ds.get("R4F0"),
    R4F1 = ds.get("R4F1"),
    R5F0 = ds.get("R5F0"),
    R5F1 = ds.get("R5F1"),
    R6F0 = ds.get("R6F0"),
    R6F1 = ds.get("R6F1"),
    R7F0 = ds.get("R7F0"),
    R7F1 = ds.get("R7F1"),
    R8F0 = ds.get("R8F0"),
    R8F1 = ds.get("R8F1"),
    R9F0 = ds.get("R9F0"),
    R9F1 = ds.get("R9F1"),
    R10F0 = ds.get("R10F0"),
    R10F1 = ds.get("R10F1"),
    R11F0 = ds.get("R11F0"),
    R11F1 = ds.get("R11F1");

    ASSERT_EQ(R0F0, "January");
    ASSERT_EQ(R0F1, "1");
    ASSERT_EQ(R1F0, "February");
    ASSERT_EQ(R1F1, "2");
    ASSERT_EQ(R2F0, "March");
    ASSERT_EQ(R2F1, "3");
    ASSERT_EQ(R3F0, "April");
    ASSERT_EQ(R3F1, "4");
    ASSERT_EQ(R4F0, "May");
    ASSERT_EQ(R4F1, "5");
    ASSERT_EQ(R5F0, "June");
    ASSERT_EQ(R5F1, "6");
    ASSERT_EQ(R6F0, "July");
    ASSERT_EQ(R6F1, "7");
    ASSERT_EQ(R7F0, "August");
    ASSERT_EQ(R7F1, "8");
    ASSERT_EQ(R8F0, "September");
    ASSERT_EQ(R8F1, "9");
    ASSERT_EQ(R9F0, "October");
    ASSERT_EQ(R9F1, "10");
    ASSERT_EQ(R10F0, "November");
    ASSERT_EQ(R10F1, "11");
    ASSERT_EQ(R11F0, "December");
    ASSERT_EQ(R11F1, "12");
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