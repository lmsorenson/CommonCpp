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
    plDataSet ds;
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv1.csv");
    plInstance str = ds.get("R0-F0");

    ASSERT_EQ(str.get(), "aaa");
}



//The last record in the file may or may not have an ending line break.
TEST_F(CSVFormatTests, TestR2_1)//has a line break
{
    plDataSet ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv1-1.csv");

    plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
}

TEST_F(CSVFormatTests, TestR2_2)//does not have a line break
{
    plDataSet ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv1.csv");

    plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
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
    plDataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv2.csv", options);

    plInstance H1 = ds.get("S0-R0-F0");
    plInstance H2 = ds.get("S0-R0-F1");
    plInstance H3 = ds.get("S0-R0-F2");
    plInstance A1 = ds.get("S1-R0-F0");
    plInstance A2 = ds.get("S1-R0-F1");
    plInstance A3 = ds.get("S1-R0-F2");
    plInstance B1 = ds.get("S1-R1-F0");
    plInstance B2 = ds.get("S1-R1-F1");
    plInstance B3 = ds.get("S1-R1-F2");

    ASSERT_EQ(H1.get(), "field_name");
    ASSERT_EQ(H2.get(), "field_name");
    ASSERT_EQ(H3.get(), "field_name");
    ASSERT_EQ(A1.get(), "aaa");
    ASSERT_EQ(A2.get(), "bbb");
    ASSERT_EQ(A3.get(), "ccc");
    ASSERT_EQ(B1.get(), "zzz");
    ASSERT_EQ(B2.get(), "yyy");
    ASSERT_EQ(B3.get(), "xxx");
} 



//Within the header and each record, there may be one or more 
//fields, separated by commas. Each line should contain the same
//number of fields throughout the file. Spaces are considered part
//of a field and should not be ignored. The last field in the record
//must not be followed by a comma. 
TEST_F(CSVFormatTests, TestR4_1)//at least one field.
{
    plDataSet ds;
    
    int32_t return_code;

    //read empty file
    return_code = ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv3-1.csv");

    //return READ_FILE_EMPTY
    ASSERT_EQ(return_code, ParseLib::READ_FORMAT_INVALID);
} 
TEST_F(CSVFormatTests, TestR4_2)//Each line should contain the same number of fields.
{
    plDataSet ds;
    
    // ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv3.csv");

    // string field1 = ds.get("R0F0");
    // string field2 = ds.get("R0F1");
    // string field3 = ds.get("R0F2");

    // ASSERT_EQ(field1, "aaa");
    // ASSERT_EQ(field2, "bbb");
    // ASSERT_EQ(field3, "ccc");
    ASSERT_EQ(1, -1);
}
TEST_F(CSVFormatTests, TestR4_3)//must not be followed by a comma
{   

    plDataSet ds;
    
    int32_t return_code;

    return_code = ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv3-2.csv");

    ASSERT_EQ(return_code, ParseLib::READ_FORMAT_INVALID);
} 



//Each field may or may not be enclosed in double quotes (however 
//some programs, such as Microsoft Excel, do not use double quotes
//at all). If fields are not enclosed with double quotes, then 
//double quotes may not appear inside the fields.
TEST_F(CSVFormatTests, TestR5)
{
    plDataSet ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv4.csv");

    plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
}  
TEST_F(CSVFormatTests, TestR5_1)//Dobule quotes may not appear inside the fields
{
    plDataSet ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv4-1.csv");

    plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
}  



//Fields containing line breaks (CRLF), double quotes, and commas
//should be enclosed in double-quotes.
TEST_F(CSVFormatTests, TestR6_1)
{
    plDataSet ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv5.csv");

    plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "b\r\rbb");
    ASSERT_EQ(field3.get(), "ccc");
}  
TEST_F(CSVFormatTests, TestR6_2)//commas can be enclosed in double quotes
{
    plDataSet ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv5-1.csv");

   plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "b,bb");
    ASSERT_EQ(field3.get(), "ccc");
}  



//If double-quotes are used to enclose fields, then a double-quote
//appearing inside a field must be escaped by preceding it with 
//another double quote. For example:
TEST_F(CSVFormatTests, TestR7)
{
    plDataSet ds;
    
    ParseLib().read_file(ds, "/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/CSV/FormatSpec/csv6.csv");

   plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "b\"bb");
    ASSERT_EQ(field3.get(), "ccc");
}  