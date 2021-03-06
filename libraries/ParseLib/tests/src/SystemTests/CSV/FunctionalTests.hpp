#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "../../TestFramework.hpp"




class CSVFunctionalSpec : public ::LucTestFramework
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
    DataSet ds;
    ParseLib().read_file(ds, this->path("test_data/test1.csv").c_str());

    Instance str = ds["R0"]["F0"];

    ASSERT_EQ(str.get(), "January");
}

TEST_F(CSVFunctionalSpec, TestR2_2)
{
    DataSet ds;
    
    int32_t exit_code = ParseLib().read_file(ds, this->path("Invalid-Path").c_str());
    
    ASSERT_EQ(exit_code, ParseLib::READ_FILE_NOT_FOUND);
    ASSERT_EQ(ds["R0"]["F0"].get(), "NO_FILE");
}

TEST_F(CSVFunctionalSpec, TestR3)
{
    DataSet ds;
    
    ParseLib().read_file(ds, this->path("test_data/test1.csv").c_str());


    //Test every value in the file.
    Instance 
    R0F0 = ds["R0"]["F0"],
    R0F1 = ds["R0"]["F1"],
    R1F0 = ds["R1"]["F0"],
    R1F1 = ds["R1"]["F1"], 
    R2F0 = ds["R2"]["F0"],
    R2F1 = ds["R2"]["F1"],
    R3F0 = ds["R3"]["F0"],
    R3F1 = ds["R3"]["F1"],
    R4F0 = ds["R4"]["F0"],
    R4F1 = ds["R4"]["F1"],
    R5F0 = ds["R5"]["F0"],
    R5F1 = ds["R5"]["F1"],
    R6F0 = ds["R6"]["F0"],
    R6F1 = ds["R6"]["F1"],
    R7F0 = ds["R7"]["F0"],
    R7F1 = ds["R7"]["F1"],
    R8F0 = ds["R8"]["F0"],
    R8F1 = ds["R8"]["F1"],
    R9F0 = ds["R9"]["F0"],
    R9F1 = ds["R9"]["F1"],
    R10F0 = ds["R10"]["F0"],
    R10F1 = ds["R10"]["F1"],
    R11F0 = ds["R11"]["F0"],
    R11F1 = ds["R11"]["F1"];

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

TEST_F(CSVFunctionalSpec, TestR3_1_1)
{
    DataSet ds;
    
    ParseLib().read_file(ds, this->path("test_data/test1.csv").c_str());
    
    Instance str = ds["R100000"]["F0"];
    

    ASSERT_EQ(str.get(), "NULL");
}

TEST_F(CSVFunctionalSpec, TestR3_1_2)
{
    DataSet ds;
    
    ParseLib().read_file(ds, this->path("test_data/test1.csv").c_str());
    
    Instance str = ds["R0"]["F0"];
    

    ASSERT_EQ(str.at(1), "NULL");
}

//Query for a single element.
// * WHERE field = value
TEST_F(CSVFunctionalSpec, TestR4_1)
{
    DataSet ds;
    ParseLib().read_file(ds, this->path("test_data/test1.csv").c_str());

    sdg::hash::DescriptorInstance descriptor_instance("F", sdg::Attribute::Scale::Numeric);
    descriptor_instance.set_value(0);

    Instance inst = ds.where(sdg::hash::KeyInstance({descriptor_instance}), "May");
    ASSERT_EQ(inst.at(1), "5");
}

//Query for a list of elements.
// 4_2 * all fields in a record
// 4_3 * all values for a specific field
TEST_F(CSVFunctionalSpec, TestR4_2)
{
    DataSet ds;
    ParseLib().read_file(ds, this->path("test_data/test1.csv").c_str());
    
    //IN -- R0
    Instance inst = ds["R0"];//get all records in record 0

    //OUT -- January,1
    ASSERT_EQ(inst.at(0) , "January");
    ASSERT_EQ(inst.at(1) , "1");
}
TEST_F(CSVFunctionalSpec, TestR4_3)
{
    DataSet ds;
    ParseLib().read_file(ds, this->path("test_data/test1.csv").c_str());
    
    //IN -- F1
    Instance inst = ds["F1"];//get all records in field 0

    //OUT -- January,1
    ASSERT_EQ(inst.at(0), "1");
    ASSERT_EQ(inst.at(1), "2");
    ASSERT_EQ(inst.at(2), "3");
    ASSERT_EQ(inst.at(3), "4");
    ASSERT_EQ(inst.at(4), "5");
    ASSERT_EQ(inst.at(5), "6");
    ASSERT_EQ(inst.at(6), "7");
    ASSERT_EQ(inst.at(7), "8");
    ASSERT_EQ(inst.at(8), "9");
    ASSERT_EQ(inst.at(9), "10");
    ASSERT_EQ(inst.at(10), "11");
    ASSERT_EQ(inst.at(11), "12");
}

// Query for an Instance's related entities.
// * 5_1: Get an associated record
// * 5_2: Get an associated field
// * 5_3: Get a value and iterate through other fields in a record.
// * 5_4: Get a value and iterate through other records in a field.
// * 5_5: Get a value name from the header.
TEST_F(CSVFunctionalSpec, TestR5_1)
{
    DataSet ds;
    ParseLib().read_file(ds, this->path("test_data/test1.csv").c_str());
    Instance inst = ds["R1"]["F1"];
    Instance inst2 = inst.GetRelatedInstance( sdg::hash::EntityID("R") );
    std::string str = inst2.at(1);


    ASSERT_EQ(str, "2");
}

TEST_F(CSVFunctionalSpec, TestR5_2)
{
    DataSet ds;
    ParseLib().read_file(ds, this->path("test_data/test1.csv").c_str());
    Instance inst = ds["R1"]["F1"];
    Instance inst2 = inst.GetRelatedInstance( sdg::hash::EntityID("F") );

    ASSERT_EQ(inst2.at(0), "1");
    ASSERT_EQ(inst2.at(1), "2");
    ASSERT_EQ(inst2.at(2), "3");
    ASSERT_EQ(inst2.at(3), "4");
    ASSERT_EQ(inst2.at(4), "5");
    ASSERT_EQ(inst2.at(5), "6");
    ASSERT_EQ(inst2.at(6), "7");
    ASSERT_EQ(inst2.at(7), "8");
    ASSERT_EQ(inst2.at(8), "9");
    ASSERT_EQ(inst2.at(9), "10");
    ASSERT_EQ(inst2.at(10), "11");
    ASSERT_EQ(inst2.at(11), "12");
}

TEST_F(CSVFunctionalSpec, TestR5_3)
{
    DataSet ds;
    ParseLib().read_file(ds, this->path("test_data/test1.csv").c_str());
    Instance inst = ds["R1"]["F0"];
    Instance inst2 = inst.GetNextInstance( sdg::hash::EntityID("R") );

    ASSERT_EQ(inst2.get(), "2");
}

TEST_F(CSVFunctionalSpec, TestR5_4)
{
    DataSet ds;
    ParseLib().read_file(ds, this->path("test_data/test1.csv").c_str());
    Instance inst = ds["R3"]["F0"];
    Instance inst2 = inst.GetNextInstance( sdg::hash::EntityID("F") );

    ASSERT_EQ(inst2.get(), "May");
}

TEST_F(CSVFunctionalSpec, TestR5_5)
{
    DataSet ds;
    std::vector<option> options;
    options.push_back({"header_line", true});
    ParseLib().read_file(ds, this->path("test_data/CSV/FormatSpec/csv2.csv").c_str(), options);
    Instance inst = ds["F1"];
    Instance inst2 = inst.GetRelatedInstance( sdg::hash::EntityID("H") );

    ASSERT_EQ(inst2.get(), "field_nameB");
}

// insert two values into one key.
TEST_F(CSVFunctionalSpec, R6__Two_Values_in_One_Key)
{
    // ASSERT_EQ(true, false);
}


//write a new instances
// * Add a new record at the end of the file.
// * Add a new record at the beginning of the file.
// * Add a new record at a specific position in the middle of the file.
// * Add a new field at the end of each record
// * Add a new field at the beginning of each record.
// * Add a new field in the middle of each record.
TEST_F(CSVFunctionalSpec, R7_1__Add_New_Record_to_End_of_File)
{
    //adds a new record to the end of an exsiting file.
    CSV ds;

    //reads in the file.
    ParseLib().read_file(ds, this->path("test_data/CSV/csvR7_1_read.csv").c_str());


    //asserts that one line exists and line 2 does not.
    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");
    ASSERT_EQ(ds["R1"]["F0"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F1"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F2"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F3"].get(), "NULL");

    //adds line 2 to the end of the document.
    ds.add_instance(sdg::hash::EntityID("R"), {"A2", "B2", "C2", "D2"});

    //writes the file to a new location.
    ParseLib().write_file(ds, this->path("test_data/CSV/Write/csvR7_1.csv").c_str());

    //opens the file just written.
    DataSet ds2;
    ParseLib().read_file(ds2, this->path("test_data/CSV/Write/csvR7_1.csv").c_str());

    //asserts that both lines exist.
    ASSERT_EQ(ds2["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds2["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds2["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds2["R0"]["F3"].get(), "D1");
    ASSERT_EQ(ds2["R1"]["F0"].get(), "A2");
    ASSERT_EQ(ds2["R1"]["F1"].get(), "B2");
    ASSERT_EQ(ds2["R1"]["F2"].get(), "C2");
    ASSERT_EQ(ds2["R1"]["F3"].get(), "D2");
}

TEST_F(CSVFunctionalSpec, R7_2__Add_New_Record_to_Beginning_of_File)
{
    CSV ds;

    //reads in the file.
    ParseLib().read_file(ds, this->path("test_data/CSV/csvR7_2_read.csv").c_str());

    //asserts that one line exists and line 2 does not.
    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");
    ASSERT_EQ(ds["R1"]["F0"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F1"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F2"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F3"].get(), "NULL");

    //adds line 2 to the end of the document.
    ds.add_instance(sdg::hash::EntityID("R"), {"AH", "BH", "CH", "DH"}, 0);

    //writes the file to a new location.
    ParseLib().write_file(ds, this->path("test_data/CSV/Write/csvR7_2.csv").c_str());

    //opens the file just written.
    DataSet ds2;
    ParseLib().read_file(ds2, this->path("test_data/CSV/Write/csvR7_2.csv").c_str());

    //asserts that both lines exist.
    ASSERT_EQ(ds2["R0"]["F0"].get(), "AH");
    ASSERT_EQ(ds2["R0"]["F1"].get(), "BH");
    ASSERT_EQ(ds2["R0"]["F2"].get(), "CH");
    ASSERT_EQ(ds2["R0"]["F3"].get(), "DH");
    ASSERT_EQ(ds2["R1"]["F0"].get(), "A1");
    ASSERT_EQ(ds2["R1"]["F1"].get(), "B1");
    ASSERT_EQ(ds2["R1"]["F2"].get(), "C1");
    ASSERT_EQ(ds2["R1"]["F3"].get(), "D1");

}

TEST_F(CSVFunctionalSpec, R7_3__Add_New_Record_to_Middle_of_File)
{
    //adds a new record to the end of an exsiting file.
    CSV ds;

    //reads in the file.
    ParseLib().read_file(ds, this->path("test_data/CSV/csvR7_3_read.csv").c_str());

    //asserts that one line exists and line 2 does not.
    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");
    ASSERT_EQ(ds["R1"]["F0"].get(), "A2");
    ASSERT_EQ(ds["R1"]["F1"].get(), "B2");
    ASSERT_EQ(ds["R1"]["F2"].get(), "C2");
    ASSERT_EQ(ds["R1"]["F3"].get(), "D2");
    ASSERT_EQ(ds["R2"]["F0"].get(), "A3");
    ASSERT_EQ(ds["R2"]["F1"].get(), "B3");
    ASSERT_EQ(ds["R2"]["F2"].get(), "C3");
    ASSERT_EQ(ds["R2"]["F3"].get(), "D3");
    ASSERT_EQ(ds["R3"]["F0"].get(), "A4");
    ASSERT_EQ(ds["R3"]["F1"].get(), "B4");
    ASSERT_EQ(ds["R3"]["F2"].get(), "C4");
    ASSERT_EQ(ds["R3"]["F3"].get(), "D4");

    //adds line 2 to the end of the document.
    ds.add_instance(sdg::hash::EntityID("R"), {"AM", "BM", "CM", "DM"}, 2);

    //writes the file to a new location.
    ParseLib().write_file(ds, this->path("test_data/CSV/Write/csvR7_3.csv").c_str());

    //opens the file just written.
    DataSet ds2;
    ParseLib().read_file(ds2, this->path("test_data/CSV/Write/csvR7_3.csv").c_str());

    //asserts that both lines exist.
    ASSERT_EQ(ds2["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds2["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds2["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds2["R0"]["F3"].get(), "D1");
    ASSERT_EQ(ds2["R1"]["F0"].get(), "A2");
    ASSERT_EQ(ds2["R1"]["F1"].get(), "B2");
    ASSERT_EQ(ds2["R1"]["F2"].get(), "C2");
    ASSERT_EQ(ds2["R1"]["F3"].get(), "D2");
    
    ASSERT_EQ(ds2["R2"]["F0"].get(), "AM");
    ASSERT_EQ(ds2["R2"]["F1"].get(), "BM");
    ASSERT_EQ(ds2["R2"]["F2"].get(), "CM");
    ASSERT_EQ(ds2["R2"]["F3"].get(), "DM");

    ASSERT_EQ(ds2["R3"]["F0"].get(), "A3");
    ASSERT_EQ(ds2["R3"]["F1"].get(), "B3");
    ASSERT_EQ(ds2["R3"]["F2"].get(), "C3");
    ASSERT_EQ(ds2["R3"]["F3"].get(), "D3");
    ASSERT_EQ(ds2["R4"]["F0"].get(), "A4");
    ASSERT_EQ(ds2["R4"]["F1"].get(), "B4");
    ASSERT_EQ(ds2["R4"]["F2"].get(), "C4");
    ASSERT_EQ(ds2["R4"]["F3"].get(), "D4");

}


TEST_F(CSVFunctionalSpec, R7_4__Add_Field_to_End_of_File)
{
    //adds a new record to the end of an exsiting file.
    CSV ds;

    //reads in the file.
    ParseLib().read_file(ds, this->path("test_data/CSV/csvR7_4_read.csv").c_str());


    //asserts that one line exists and line 2 does not.
    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");
    ASSERT_EQ(ds["R0"]["F4"].get(), "NULL");

    //adds line 2 to the end of the document.
    ds.add_instance(sdg::hash::EntityID("F"), {"E1"});

    //writes the file to a new location.
    ParseLib().write_file(ds, this->path("test_data/CSV/Write/csvR7_4.csv").c_str());

    //opens the file just written.
    DataSet ds2;
    ParseLib().read_file(ds2, this->path("test_data/CSV/Write/csvR7_4.csv").c_str());

    //asserts that both lines exist.
    ASSERT_EQ(ds2["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds2["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds2["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds2["R0"]["F3"].get(), "D1");
    ASSERT_EQ(ds2["R0"]["F4"].get(), "E1");
}

TEST_F(CSVFunctionalSpec, R7_5__Add_New_Field_to_Beginning_of_File)
{
    //adds a new record to the end of an exsiting file.
    CSV ds;

    //reads in the file.
    ParseLib().read_file(ds, this->path("test_data/CSV/csvR7_5_read.csv").c_str());

    //asserts that one line exists and line 2 does not.
    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");
    ASSERT_EQ(ds["R0"]["F4"].get(), "NULL");

    //adds line 2 to the end of the document.
    ds.add_instance(sdg::hash::EntityID("F"), {"N1"}, 0);

    //writes the file to a new location.
    ParseLib().write_file(ds, this->path("test_data/CSV/Write/csvR7_5.csv").c_str());

    //opens the file just written.
    DataSet ds2;
    ParseLib().read_file(ds2, this->path("test_data/CSV/Write/csvR7_5.csv").c_str());

    //asserts that both lines exist.
    ASSERT_EQ(ds2["R0"]["F0"].get(), "N1");//new field at beginning
    ASSERT_EQ(ds2["R0"]["F1"].get(), "A1");
    ASSERT_EQ(ds2["R0"]["F2"].get(), "B1");
    ASSERT_EQ(ds2["R0"]["F3"].get(), "C1");
    ASSERT_EQ(ds2["R0"]["F4"].get(), "D1");

}

TEST_F(CSVFunctionalSpec, R7_6__Add_New_Field_to_Middle_of_File)
{
    CSV ds;

    //reads in the file.
    ParseLib().read_file(ds, this->path("test_data/CSV/csvR7_6_read.csv").c_str());

    //asserts that one line exists and line 2 does not.
    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");

    ASSERT_EQ(ds["R1"]["F0"].get(), "A2");
    ASSERT_EQ(ds["R1"]["F1"].get(), "B2");
    ASSERT_EQ(ds["R1"]["F2"].get(), "C2");
    ASSERT_EQ(ds["R1"]["F3"].get(), "D2");

    ASSERT_EQ(ds["R2"]["F0"].get(), "A3");
    ASSERT_EQ(ds["R2"]["F1"].get(), "B3");
    ASSERT_EQ(ds["R2"]["F2"].get(), "C3");
    ASSERT_EQ(ds["R2"]["F3"].get(), "D3");
    
    ASSERT_EQ(ds["R3"]["F0"].get(), "A4");
    ASSERT_EQ(ds["R3"]["F1"].get(), "B4");
    ASSERT_EQ(ds["R3"]["F2"].get(), "C4");
    ASSERT_EQ(ds["R3"]["F3"].get(), "D4");

    //adds line 2 to the end of the document.
    ds.add_instance(sdg::hash::EntityID("F"), {"NF", "NF", "NF", "NF"}, 2);

    //writes the file to a new location.
    ParseLib().write_file(ds, this->path("test_data/CSV/Write/csvR7_6.csv").c_str());

    //opens the file just written.
    DataSet ds2;
    ParseLib().read_file(ds2, this->path("test_data/CSV/Write/csvR7_6.csv").c_str());

    //asserts that both lines exist.
    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "NF");//new field
    ASSERT_EQ(ds["R0"]["F3"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F4"].get(), "D1");

    ASSERT_EQ(ds["R1"]["F0"].get(), "A2");
    ASSERT_EQ(ds["R1"]["F1"].get(), "B2");
    ASSERT_EQ(ds["R1"]["F2"].get(), "NF");//new field
    ASSERT_EQ(ds["R1"]["F3"].get(), "C2");
    ASSERT_EQ(ds["R1"]["F4"].get(), "D2");

    ASSERT_EQ(ds["R2"]["F0"].get(), "A3");
    ASSERT_EQ(ds["R2"]["F1"].get(), "B3");
    ASSERT_EQ(ds["R2"]["F2"].get(), "NF");//new field
    ASSERT_EQ(ds["R2"]["F3"].get(), "C3");
    ASSERT_EQ(ds["R2"]["F4"].get(), "D3");
    
    ASSERT_EQ(ds["R3"]["F0"].get(), "A4");
    ASSERT_EQ(ds["R3"]["F1"].get(), "B4");
    ASSERT_EQ(ds["R3"]["F2"].get(), "NF");//new field
    ASSERT_EQ(ds["R3"]["F3"].get(), "C4");
    ASSERT_EQ(ds["R3"]["F4"].get(), "D4");

}

//Modify instances.
// * delete a record instance.
// * move a record instance to a different position.
// * overwrite a field in an existing record.
// * overwrite all fields in an existing record.
TEST_F(CSVFunctionalSpec, R8_1__Delete_a_Record)//delete a record
{
    CSV ds;

    //create three records
    ds.add_instance(sdg::hash::EntityID("R"), {"A1", "B1", "C1", "D1"});
    ds.add_instance(sdg::hash::EntityID("R"), {"A2", "B2", "C2", "D2"});

    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");

    ASSERT_EQ(ds["R1"]["F0"].get(), "A2");
    ASSERT_EQ(ds["R1"]["F1"].get(), "B2");
    ASSERT_EQ(ds["R1"]["F2"].get(), "C2");
    ASSERT_EQ(ds["R1"]["F3"].get(), "D2");

    ds.remove_instance(sdg::hash::KeyInstance("R1"));//remove row 3

    //assert row 3 = NULL
    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");

    ASSERT_EQ(ds["R1"]["F0"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F1"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F2"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F3"].get(), "NULL");

    ParseLib().write_file(ds, this->path("test_data/CSV/Write/csvR8_1.csv").c_str());
    DataSet ds2;
    ParseLib().read_file(ds2, this->path("test_data/CSV/Write/csvR8_1.csv").c_str());

    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");

    ASSERT_EQ(ds["R1"]["F0"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F1"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F2"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F3"].get(), "NULL");
}

TEST_F(CSVFunctionalSpec, R8_2__Move_a_Record)//move a record
{
    CSV ds;

    //create three records
    ds.add_instance(sdg::hash::EntityID("R"), {"A1", "B1", "C1", "D1"});
    ds.add_instance(sdg::hash::EntityID("R"), {"A2", "B2", "C2", "D2"});

    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");

    ASSERT_EQ(ds["R1"]["F0"].get(), "A2");
    ASSERT_EQ(ds["R1"]["F1"].get(), "B2");
    ASSERT_EQ(ds["R1"]["F2"].get(), "C2");
    ASSERT_EQ(ds["R1"]["F3"].get(), "D2");

    sdg::hash::DescriptorInstance descriptor = sdg::hash::DescriptorInstance("R", sdg::Attribute::Scale::Numeric);
    descriptor.set_value(1);
    ds.reposition_instance(descriptor);//remove row 3

    //assert row 3 = NULL
    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");

    ASSERT_EQ(ds["R1"]["F0"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F1"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F2"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F3"].get(), "NULL");

    ASSERT_EQ(ds["R2"]["F0"].get(), "A2");
    ASSERT_EQ(ds["R2"]["F1"].get(), "B2");
    ASSERT_EQ(ds["R2"]["F2"].get(), "C2");
    ASSERT_EQ(ds["R2"]["F3"].get(), "D2");

    ParseLib().write_file(ds, this->path("test_data/CSV/Write/csvR8_2.csv").c_str());

    DataSet ds2;
    ParseLib().read_file(ds2, this->path("test_data/CSV/Write/csvR8_2.csv").c_str());

    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");

    ASSERT_EQ(ds["R1"]["F0"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F1"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F2"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F3"].get(), "NULL");
    
    ASSERT_EQ(ds["R2"]["F0"].get(), "A2");
    ASSERT_EQ(ds["R2"]["F1"].get(), "B2");
    ASSERT_EQ(ds["R2"]["F2"].get(), "C2");
    ASSERT_EQ(ds["R2"]["F3"].get(), "D2");
}

TEST_F(CSVFunctionalSpec, R8_3__Overwrite_a_Record)//move a record into a location that already has a record
{
    CSV ds;

    //create four records
    ds.add_instance(sdg::hash::EntityID("R"), {"A1", "B1", "C1", "D1"});
    ds.add_instance(sdg::hash::EntityID("R"), {"A2", "B2", "C2", "D2"});
    ds.add_instance(sdg::hash::EntityID("R"), {"A3", "B3", "C3", "D3"});
    ds.add_instance(sdg::hash::EntityID("R"), {"A4", "B4", "C4", "D4"});

    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");

    ASSERT_EQ(ds["R1"]["F0"].get(), "A2");
    ASSERT_EQ(ds["R1"]["F1"].get(), "B2");
    ASSERT_EQ(ds["R1"]["F2"].get(), "C2");
    ASSERT_EQ(ds["R1"]["F3"].get(), "D2");

    ASSERT_EQ(ds["R2"]["F0"].get(), "A3");
    ASSERT_EQ(ds["R2"]["F1"].get(), "B3");
    ASSERT_EQ(ds["R2"]["F2"].get(), "C3");
    ASSERT_EQ(ds["R2"]["F3"].get(), "D3");
    
    ASSERT_EQ(ds["R3"]["F0"].get(), "A4");
    ASSERT_EQ(ds["R3"]["F1"].get(), "B4");
    ASSERT_EQ(ds["R3"]["F2"].get(), "C4");
    ASSERT_EQ(ds["R3"]["F3"].get(), "D4");

    sdg::hash::DescriptorInstance descriptor = sdg::hash::DescriptorInstance("R", sdg::Attribute::Scale::Numeric);
    descriptor.set_value(1);
    ds.reposition_instance(descriptor);//remove row 3

    //assert row 3 = NULL
    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");

    ASSERT_EQ(ds["R1"]["F0"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F1"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F2"].get(), "NULL");
    ASSERT_EQ(ds["R1"]["F3"].get(), "NULL");

    ASSERT_EQ(ds["R2"]["F0"].get(), "A2");
    ASSERT_EQ(ds["R2"]["F1"].get(), "B2");
    ASSERT_EQ(ds["R2"]["F2"].get(), "C2");
    ASSERT_EQ(ds["R2"]["F3"].get(), "D2");

    ASSERT_EQ(ds["R3"]["F0"].get(), "A3");
    ASSERT_EQ(ds["R3"]["F1"].get(), "B3");
    ASSERT_EQ(ds["R3"]["F2"].get(), "C3");
    ASSERT_EQ(ds["R3"]["F3"].get(), "D3");
    
    ASSERT_EQ(ds["R4"]["F0"].get(), "A4");
    ASSERT_EQ(ds["R4"]["F1"].get(), "B4");
    ASSERT_EQ(ds["R4"]["F2"].get(), "C4");
    ASSERT_EQ(ds["R4"]["F3"].get(), "D4");
}

//Create a write transaction on an empty file path.
TEST_F(CSVFunctionalSpec, R9__Write_New_File)
{
    //adds a new record to the end of a 
    CSV ds;
    ds.add_instance(sdg::hash::EntityID("R"), {"A1", "B1", "C1", "D1"});
    ds.add_instance(sdg::hash::EntityID("R"), {"A2", "B2", "C2", "D2"});

    ASSERT_EQ(ds["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds["R0"]["F3"].get(), "D1");

    ASSERT_EQ(ds["R1"]["F0"].get(), "A2");
    ASSERT_EQ(ds["R1"]["F1"].get(), "B2");
    ASSERT_EQ(ds["R1"]["F2"].get(), "C2");
    ASSERT_EQ(ds["R1"]["F3"].get(), "D2");

    ParseLib().write_file(ds, this->path("test_data/CSV/Write/csvR9.csv").c_str());

    DataSet ds2;
    std::cout << "path: " << this->path("test_data/CSV/Write/csvR9.csv").c_str() << std::endl;
    ParseLib().read_file(ds2, this->path("test_data/CSV/Write/csvR9.csv").c_str());

    ASSERT_EQ(ds2["R0"]["F0"].get(), "A1");
    ASSERT_EQ(ds2["R0"]["F1"].get(), "B1");
    ASSERT_EQ(ds2["R0"]["F2"].get(), "C1");
    ASSERT_EQ(ds2["R0"]["F3"].get(), "D1");

    ASSERT_EQ(ds2["R1"]["F0"].get(), "A2");
    ASSERT_EQ(ds2["R1"]["F1"].get(), "B2");
    ASSERT_EQ(ds2["R1"]["F2"].get(), "C2");
    ASSERT_EQ(ds2["R1"]["F3"].get(), "D2");
}

