#include <string>
#include <iostream>

#include <gtest/gtest.h>
#include <file_inst.h>

using namespace std;


class CSVTest : public ::testing::Test
{
protected:
    
    CSVTest() {
    }
    
    virtual ~CSVTest() {
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

class Test : public ::testing::Test
{
protected:
    
    Test() {
    }
    
    virtual ~Test() {
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


TEST_F(Test, Test4)
{
    Filum().read_file("/Users/lucassorenson/Code/Common/CommonCpp/tests/test_data/test1.csv");

    ASSERT_EQ(true, false);
}

TEST_F(Test, Test5)
{
    Filum().write_file();
    ASSERT_EQ(true, false);
}

int main(int argc, char **argv)
{

    ::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
