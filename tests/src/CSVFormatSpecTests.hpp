#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.h>


class CSVFormatTests : public ::testing::Test
{
protected:
    
    CSVFormatTests() {
    }
    
    virtual ~CSVFormatTests() {
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



//Each record is located on a separate line, delimited by a line break (CRLF). 
TEST_F(CSVFormatTests, TestR1)
{
    AbstractDataStructure ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv1.csv");

    string str = ds.get("R0F0");

    ASSERT_EQ(str, "aaa");
}



//The last record in the file may or may not have an ending line break.
TEST_F(CSVFormatTests, TestR2)
{
    AbstractDataStructure ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv1.csv");

    string str = ds.get("R0F0");

    ASSERT_EQ(str, "January");
}



//There maybe an optional header line appearing as the first line
//of the file with the same format as normal record lines. This 
//header will contain names corresponding to the fields in the 
//file and should contain the same number of fields as the records
// in the rest of the file (the presence or absence of the header 
//line should be indicated via the optional "header" parameter of
//this MIME type).
TEST_F(CSVFormatTests, TestR3)
{
    AbstractDataStructure ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv2.csv");

    string str = ds.get("R0F0");

    ASSERT_EQ(str, "January");
} 



//Within the header and each record, there may be one or more 
//fields, separated by commas. Each line should contain the same
//number of fields throughout the file. Spaces are considered part
//of a field and should not be ignored. The last field in the record
//must not be followed by a comma. 
TEST_F(CSVFormatTests, TestR4)
{
    AbstractDataStructure ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv3.csv");

    string str = ds.get("R0F0");

    ASSERT_EQ(str, "January");
} 



//Each field may or may not be enclosed in double quotes (however 
//some programs, such as Microsoft Excel, do not use double quotes
//at all). If fields are not enclosed with double quotes, then 
//double quotes may not appear inside the fields.
TEST_F(CSVFormatTests, TestR5)
{
    AbstractDataStructure ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv4.csv");

    string field1 = ds.get("R0F0");
    string field2 = ds.get("R0F1");
    string field3 = ds.get("R0F2");

    ASSERT_EQ(field1, "aaa");
    ASSERT_EQ(field2, "bbb");
    ASSERT_EQ(field3, "ccc");
}  



//Fields containing line breaks (CRLF), double quotes, and commas
//should be enclosed in double-quotes.
TEST_F(CSVFormatTests, TestR6)
{
    AbstractDataStructure ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv5.csv");

    string str = ds.get("R0F0");

    ASSERT_EQ(str, "January");
}  



//If double-quotes are used to enclose fields, then a double-quote
//appearing inside a field must be escaped by preceding it with 
//another double quote. For example:
TEST_F(CSVFormatTests, TestR7)
{
    AbstractDataStructure ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv6.csv");

    string str = ds.get("R0F0");

    ASSERT_EQ(str, "January");
}  