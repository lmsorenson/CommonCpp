#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "TestFramework.hpp"


class CSVFormatTests : public ::LucTestFramework
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
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv1.csv").c_str());
    //plInstance str = ds['A']['1'];
    // plInstance str = ds.get("R0-F0");
    plInstance str = ds["R0"]["F0"];

    ASSERT_EQ(str.get(), "aaa");
}
//HEADER 
TEST_F(CSVFormatTests, TestR1_WithHeader)
{
    plDataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv1H.csv").c_str(), options);
    plInstance str = ds["R0"]["F0"];

    ASSERT_EQ(str.get(), "aaa");
}



//The last record in the file may or may not have an ending line break.
TEST_F(CSVFormatTests, TestR2_1)//has a line break
{
    plDataSet ds;
    
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv1-1.csv").c_str());

    plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
}
//The last record in the file may or may not have an ending line break.
TEST_F(CSVFormatTests, TestR2_1_WithHeader)//has a line break
{
    plDataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv1-1H.csv").c_str(), options);

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
    
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv1.csv").c_str());

    plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
}

TEST_F(CSVFormatTests, TestR2_2_WithHeader)//does not have a line break
{
    plDataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv1H.csv").c_str(), options);

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
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv2.csv").c_str(), options);

    plInstance H1 = ds.get("H-R0-F0");
    plInstance H2 = ds.get("H-R0-F1");
    plInstance H3 = ds.get("H-R0-F2");
    plInstance A1 = ds.get("R0-F0");
    plInstance A2 = ds.get("R0-F1");
    plInstance A3 = ds.get("R0-F2");
    plInstance B1 = ds.get("R1-F0");
    plInstance B2 = ds.get("R1-F1");
    plInstance B3 = ds.get("R1-F2");

    ASSERT_EQ(H1.get(), "field_nameA");
    ASSERT_EQ(H2.get(), "field_nameB");
    ASSERT_EQ(H3.get(), "field_nameC");
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
    return_code = ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv3-1.csv").c_str());

    //return READ_FILE_EMPTY
    ASSERT_EQ(return_code, ParseLib::READ_FORMAT_INVALID);
    ASSERT_EQ(ds.get("R0-F1").get(), "NULL");
} 
TEST_F(CSVFormatTests, TestR4_1_WithHeader)//at least one field.
{
    plDataSet ds;
    
    int32_t return_code;

    //read empty file
    std::vector<option> options;
    options.push_back({"header_line", true});
    return_code = ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv3-1.csv").c_str(), options);

    //return READ_FILE_EMPTY
    ASSERT_EQ(return_code, ParseLib::READ_FORMAT_INVALID);
    ASSERT_EQ(ds.get("R0-F1").get(), "NULL");
} 
TEST_F(CSVFormatTests, TestR4_2)//Each line should contain the same number of fields.
{
    plDataSet ds;
    
    int32_t return_code;

    return_code = ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv3-3.csv").c_str());

    ASSERT_EQ(return_code, ParseLib::READ_FORMAT_INVALID);
    ASSERT_EQ(ds.get("R0-F1").get(), "NULL");
}
TEST_F(CSVFormatTests, TestR4_2_WithHeader)//Each line should contain the same number of fields.
{
    plDataSet ds;
    
    int32_t return_code;
    std::vector<option> options;
    options.push_back({"header_line", true});
    return_code = ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv3-3H.csv").c_str(), options);

    ASSERT_EQ(return_code, ParseLib::READ_FORMAT_INVALID);
    ASSERT_EQ(ds.get("R0-F1").get(), "NULL");
}
TEST_F(CSVFormatTests, TestR4_3)//must not be followed by a comma
{   

    plDataSet ds;
    
    int32_t return_code;

    return_code = ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv3-2.csv").c_str());

    ASSERT_EQ(return_code, ParseLib::READ_FORMAT_INVALID);
    ASSERT_EQ(ds.get("R0-F1").get(), "NULL");
} 
TEST_F(CSVFormatTests, TestR4_3_WithHeader)//must not be followed by a comma
{   
    plDataSet ds;
    
    int32_t return_code;
    std::vector<option> options;
    options.push_back({"header_line", true});
    return_code = ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv3-2H.csv").c_str(), options);

    ASSERT_EQ(return_code, ParseLib::READ_FORMAT_INVALID);
    ASSERT_EQ(ds.get("R0-F1").get(), "NULL");
} 



//Each field may or may not be enclosed in double quotes (however 
//some programs, such as Microsoft Excel, do not use double quotes
//at all). If fields are not enclosed with double quotes, then 
//double quotes may not appear inside the fields.
TEST_F(CSVFormatTests, TestR5)
{
    plDataSet ds;
    
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv4.csv").c_str());

    plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
}  
TEST_F(CSVFormatTests, TestR5_WithHeader)
{
    plDataSet ds;
    
    std::vector<option> options;
    options.push_back({"header_line", true});
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv4H.csv").c_str(), options);

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
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv4-1.csv").c_str());

    plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
}  
TEST_F(CSVFormatTests, TestR5_1_WithHeader)//Dobule quotes may not appear inside the fields
{
    plDataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv4-1H.csv").c_str(), options);

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

    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv5.csv").c_str());

    plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "b\r\rbb");
    ASSERT_EQ(field3.get(), "ccc");
}  
TEST_F(CSVFormatTests, TestR6_1_WithHeader)
{
    plDataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv5H.csv").c_str(), options);

    plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "b\r\r\rbb");
    ASSERT_EQ(field3.get(), "ccc");
} 
TEST_F(CSVFormatTests, TestR6_2)//commas can be enclosed in double quotes
{
    plDataSet ds;
    
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv5-1.csv").c_str());

   plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "b,bb");
    ASSERT_EQ(field3.get(), "ccc");
}  
TEST_F(CSVFormatTests, TestR6_2_WithHeader)//commas can be enclosed in double quotes
{
    plDataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv5-1H.csv").c_str(), options);

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
    
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv6.csv").c_str());

   plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "b\"bb");
    ASSERT_EQ(field3.get(), "ccc");
}  
TEST_F(CSVFormatTests, TestR7_WithHeader)
{
    plDataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ParseLib().read_file(ds, this->path("../test_data/CSV/FormatSpec/csv6H.csv").c_str(), options);

   plInstance
        field1 = ds.get("R0-F0"),
        field2 = ds.get("R0-F1"),
        field3 = ds.get("R0-F2");

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "b\"bb");
    ASSERT_EQ(field3.get(), "ccc");
}  