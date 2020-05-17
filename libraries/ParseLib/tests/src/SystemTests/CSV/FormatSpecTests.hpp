#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "../../TestFramework.hpp"

using sdg::DataSet;
using sdg::Instance;
using sdg::ParseLib;
using sdg::CSV;
using sdg::option;


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
    DataSet ds;

    ds.Read(this->path("test_data/CSV/FormatSpec/csv1.csv"));
    // ParseLib().read_file(ds, this->path("test_data/CSV/FormatSpec/csv1.csv").c_str());
    //Instance str = ds['A']['1'];
    // Instance str = ds.get("R0-F0");
    Instance str = ds["R0"]["F0"];

    ASSERT_EQ(str.get(), "aaa");
}
//HEADER 
TEST_F(CSVFormatTests, TestR1_WithHeader)
{
    DataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ds.Read(this->path("test_data/CSV/FormatSpec/csv1H.csv"), options);
    Instance str = ds["R0"]["F0"];

    ASSERT_EQ(str.get(), "aaa");
}



//The last record in the file may or may not have an ending line break.
TEST_F(CSVFormatTests, TestR2_1)//has a line break
{
    DataSet ds;
    
   ds.Read(this->path("test_data/CSV/FormatSpec/csv1-1.csv"));

    Instance
        field1 = ds["R0"]["F0"],
        field2 = ds["R0"]["F1"],
        field3 = ds["R0"]["F2"];

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
}
//The last record in the file may or may not have an ending line break.
TEST_F(CSVFormatTests, TestR2_1_WithHeader)//has a line break
{
    DataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ds.Read( this->path("test_data/CSV/FormatSpec/csv1-1H.csv"), options);

    Instance
        field1 = ds["R0"]["F0"],
        field2 = ds["R0"]["F1"],
        field3 = ds["R0"]["F2"];

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
}

TEST_F(CSVFormatTests, TestR2_2)//does not have a line break
{
    DataSet ds;
    
    ds.Read(this->path("test_data/CSV/FormatSpec/csv1.csv"));

    Instance
        field1 = ds["R0"]["F0"],
        field2 = ds["R0"]["F1"],
        field3 = ds["R0"]["F2"];

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
}

TEST_F(CSVFormatTests, TestR2_2_WithHeader)//does not have a line break
{
    DataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ds.Read( this->path("test_data/CSV/FormatSpec/csv1H.csv"), options );

    Instance
        field1 = ds["R0"]["F0"],
        field2 = ds["R0"]["F1"],
        field3 = ds["R0"]["F2"];

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
    DataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ds.Read(this->path("test_data/CSV/FormatSpec/csv2.csv"), options );

    Instance H1 = ds["H"]["R0"]["F0"];
    Instance H2 = ds["H"]["R0"]["F1"];
    Instance H3 = ds["H"]["R0"]["F2"];
    Instance A1 = ds["R0"]["F0"];
    Instance A2 = ds["R0"]["F1"];
    Instance A3 = ds["R0"]["F2"];
    Instance B1 = ds["R1"]["F0"];
    Instance B2 = ds["R1"]["F1"];
    Instance B3 = ds["R1"]["F2"];

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
    DataSet ds;
    int32_t return_code;

    //read empty file
    ds.Read(this->path("test_data/CSV/FormatSpec/csv3-1.csv"), &return_code);

    //return READ_FILE_EMPTY
    ASSERT_EQ(return_code, ParseLib::READ_FORMAT_INVALID);
    ASSERT_EQ(ds["R0"]["F1"].get(), "NULL");
} 
TEST_F(CSVFormatTests, TestR4_1_WithHeader)//at least one field.
{
    //todo - bad test, succeeds when it should fail
    DataSet ds;
    
    int32_t return_code;

    //read empty file
    std::vector<option> options;
    options.push_back({"header_line", true});
    ds.Read(this->path("test_data/CSV/FormatSpec/csv3-1.csv"), options, &return_code);

    //return READ_FILE_EMPTY
    ASSERT_EQ(return_code, ParseLib::READ_FORMAT_INVALID);
    ASSERT_EQ(ds["R0"]["F1"].get(), "NULL");
} 
TEST_F(CSVFormatTests, TestR4_2)//Each line should contain the same number of fields.
{
    DataSet ds;
    int32_t return_code;
    
    ds.Read(this->path("test_data/CSV/FormatSpec/csv3-3.csv"), &return_code);

    ASSERT_EQ(return_code, ParseLib::READ_FORMAT_INVALID);
    ASSERT_EQ(ds["R0"]["F1"].get(), "NULL");
}
TEST_F(CSVFormatTests, TestR4_2_WithHeader)//Each line should contain the same number of fields.
{
    DataSet ds;
    int32_t return_code;
    std::vector<option> options;
    options.push_back({"header_line", true});

    ds.Read(this->path("test_data/CSV/FormatSpec/csv3-3H.csv"), options, &return_code);

    ASSERT_EQ(return_code, ParseLib::READ_FORMAT_INVALID);
    ASSERT_EQ(ds["R0"]["F1"].get(), "NULL");
}
TEST_F(CSVFormatTests, TestR4_3)//must not be followed by a comma
{   
    DataSet ds;
    int32_t return_code;

    ds.Read(this->path("test_data/CSV/FormatSpec/csv3-2.csv"), &return_code);

    ASSERT_EQ(return_code, ParseLib::READ_FORMAT_INVALID);
    ASSERT_EQ(ds["R0"]["F1"].get(), "NULL");
} 
TEST_F(CSVFormatTests, TestR4_3_WithHeader)//must not be followed by a comma
{   
    DataSet ds;
    
    int32_t return_code;
    std::vector<option> options;
    options.push_back({"header_line", true});

    ds.Read(this->path("test_data/CSV/FormatSpec/csv3-2H.csv"), options, &return_code);

    ASSERT_EQ(return_code, ParseLib::READ_FORMAT_INVALID);
    ASSERT_EQ(ds["R0"]["F1"].get(), "NULL");
} 



//Each field may or may not be enclosed in double quotes (however 
//some programs, such as Microsoft Excel, do not use double quotes
//at all). If fields are not enclosed with double quotes, then 
//double quotes may not appear inside the fields.
TEST_F(CSVFormatTests, TestR5)
{
    DataSet ds;
    
    ds.Read(this->path("test_data/CSV/FormatSpec/csv4.csv"));

    Instance
        field1 = ds["R0"]["F0"],
        field2 = ds["R0"]["F1"],
        field3 = ds["R0"]["F2"];

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
}  
TEST_F(CSVFormatTests, TestR5_WithHeader)
{
    DataSet ds;
    
    std::vector<option> options;
    options.push_back({"header_line", true});
    ds.Read(this->path("test_data/CSV/FormatSpec/csv4H.csv"), options);

    Instance
        field1 = ds["R0"]["F0"],
        field2 = ds["R0"]["F1"],
        field3 = ds["R0"]["F2"];

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
} 
TEST_F(CSVFormatTests, TestR5_1)//Dobule quotes may not appear inside the fields
{
    DataSet ds;
    ds.Read(this->path("test_data/CSV/FormatSpec/csv4-1.csv"));

    Instance
        field1 = ds["R0"]["F0"],
        field2 = ds["R0"]["F1"],
        field3 = ds["R0"]["F2"];

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
}  
TEST_F(CSVFormatTests, TestR5_1_WithHeader)//Dobule quotes may not appear inside the fields
{
    DataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});

    ds.Read(this->path("test_data/CSV/FormatSpec/csv4-1H.csv"), options);

    Instance
        field1 = ds["R0"]["F0"],
        field2 = ds["R0"]["F1"],
        field3 = ds["R0"]["F2"];

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "bbb");
    ASSERT_EQ(field3.get(), "ccc");
} 



//Fields containing line breaks (CRLF), double quotes, and commas
//should be enclosed in double-quotes.
TEST_F(CSVFormatTests, TestR6_1)
{
    DataSet ds;

    ds.Read(this->path("test_data/CSV/FormatSpec/csv5.csv"));

    Instance
        field1 = ds["R0"]["F0"],
        field2 = ds["R0"]["F1"],
        field3 = ds["R0"]["F2"];

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "b\r\nbb");
    ASSERT_EQ(field3.get(), "ccc");
}  
TEST_F(CSVFormatTests, TestR6_1_WithHeader)
{
    DataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ds.Read(this->path("test_data/CSV/FormatSpec/csv5H.csv"), options);

    Instance
        field1 = ds["R0"]["F0"],
        field2 = ds["R0"]["F1"],
        field3 = ds["R0"]["F2"];

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "b\r\r\rbb");
    ASSERT_EQ(field3.get(), "ccc");
} 
TEST_F(CSVFormatTests, TestR6_2)//commas can be enclosed in double quotes
{
    DataSet ds;
    
    ds.Read(this->path("test_data/CSV/FormatSpec/csv5-1.csv"));

   Instance
        field1 = ds["R0"]["F0"],
        field2 = ds["R0"]["F1"],
        field3 = ds["R0"]["F2"];

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "b,bb");
    ASSERT_EQ(field3.get(), "ccc");
}  
TEST_F(CSVFormatTests, TestR6_2_WithHeader)//commas can be enclosed in double quotes
{
    DataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});

    ds.Read(this->path("test_data/CSV/FormatSpec/csv5-1H.csv"), options);

   Instance
        field1 = ds["R0"]["F0"],
        field2 = ds["R0"]["F1"],
        field3 = ds["R0"]["F2"];

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "b,bb");
    ASSERT_EQ(field3.get(), "ccc");
} 



//If double-quotes are used to enclose fields, then a double-quote
//appearing inside a field must be escaped by preceding it with 
//another double quote. For example:
TEST_F(CSVFormatTests, TestR7)
{
    DataSet ds;
    
    ds.Read(this->path("test_data/CSV/FormatSpec/csv6.csv"));

   Instance
        field1 = ds["R0"]["F0"],
        field2 = ds["R0"]["F1"],
        field3 = ds["R0"]["F2"];

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "b\"bb");
    ASSERT_EQ(field3.get(), "ccc");
}  
TEST_F(CSVFormatTests, TestR7_WithHeader)
{
    DataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ds.Read(this->path("test_data/CSV/FormatSpec/csv6H.csv"), options);

   Instance
        field1 = ds["R0"]["F0"],
        field2 = ds["R0"]["F1"],
        field3 = ds["R0"]["F2"];

    ASSERT_EQ(field1.get(), "aaa");
    ASSERT_EQ(field2.get(), "b\"bb");
    ASSERT_EQ(field3.get(), "ccc");
}  