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

//
TEST_F(CSVFunctionalSpec, TestR1)
{
    plDataSet ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/test1.csv");

    plInstance str = ds.get("R0F0");

    ASSERT_EQ(str.get(), "January");
}

TEST_F(CSVFunctionalSpec, TestR2_2)
{
    plDataSet ds;
    
    int32_t exit_code = ParseLib().read_file(ds, "Invalid-Path");
    
    ASSERT_EQ(exit_code, 1);
    ASSERT_EQ(ds.get("R0F0").get(), "file_not_found");
}

TEST_F(CSVFunctionalSpec, TestR3)
{
    plDataSet ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/test1.csv");


    //Test every value in the file.
    plInstance 
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

    ASSERT_EQ(R0F0.get(), "January");
    ASSERT_EQ(R0F1.get(), "1");
    ASSERT_EQ(R1F0.get(), "February");
    ASSERT_EQ(R1F1.get(), "2");
    ASSERT_EQ(R2F0.get(), "March");
    ASSERT_EQ(R2F1.get(), "3");
    ASSERT_EQ(R3F0.get(), "April");
    ASSERT_EQ(R3F1.get(), "4");
    ASSERT_EQ(R4F0.get(), "May");
    ASSERT_EQ(R4F1.get(), "5");
    ASSERT_EQ(R5F0.get(), "June");
    ASSERT_EQ(R5F1.get(), "6");
    ASSERT_EQ(R6F0.get(), "July");
    ASSERT_EQ(R6F1.get(), "7");
    ASSERT_EQ(R7F0.get(), "August");
    ASSERT_EQ(R7F1.get(), "8");
    ASSERT_EQ(R8F0.get(), "September");
    ASSERT_EQ(R8F1.get(), "9");
    ASSERT_EQ(R9F0.get(), "October");
    ASSERT_EQ(R9F1.get(), "10");
    ASSERT_EQ(R10F0.get(), "November");
    ASSERT_EQ(R10F1.get(), "11");
    ASSERT_EQ(R11F0.get(), "December");
    ASSERT_EQ(R11F1.get(), "12");
}

TEST_F(CSVFunctionalSpec, TestR3_1)
{
    plDataSet ds;
    
    int32_t exit_code = ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/test1.csv");
    
    plInstance str = ds.get("R100000F0");
    

    ASSERT_EQ(str.get(), "data_not_found");
}

//Query for a single element.
// * WHERE field = value
TEST_F(CSVFunctionalSpec, TestR4_1)
{
    plDataSet ds;
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/test1.csv");
    plInstance inst = ds.get("R0F0");
    // inst = inst.related("R");//line retrieves a related record.

    ASSERT_EQ(inst.get(), "slkd");
}

//Query for a list of elements.
// * all fields in a record
// * all values for a specific field
TEST_F(CSVFunctionalSpec, TestR4_2)
{
    ASSERT_EQ(true, false);
}

// Query for an Instance's related entities.
// * get a field and iterate through other fields in a record.
// * get a filed and iterate through other records in a field.
// * get a field name from the header.
TEST_F(CSVFunctionalSpec, TestR5)
{
    ASSERT_EQ(true, false);
}

// insert two values into one key.
TEST_F(CSVFunctionalSpec, TestR6)
{
    ASSERT_EQ(true, false);
}


//write a new instances
// * Add a new record at the end of the file.
// * Add a new record at the beginning of the file.
// * Add a new record at a specific position in the middle of the file.
// * Add a new field at the end of each record
// * Add a new field at the beginning of each record.
// * Add a new field in the middle of each record.
TEST_F(CSVFunctionalSpec, TestR7)
{
    ASSERT_EQ(true, false);
}

//Modify instances.
// * overwrite a field in an existing record.
// * overwrite all fields in an existing record.
TEST_F(CSVFunctionalSpec, TestR8)
{
    ASSERT_EQ(true, false);
}

//Create a write transaction on an empty file path.
TEST_F(CSVFunctionalSpec, TestR9)
{
    ASSERT_EQ(true, false);
}

