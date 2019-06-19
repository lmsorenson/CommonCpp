#include <string>
#include <iostream>

#include <gtest/gtest.h>

using namespace std;


class FooTest : public ::testing::Test
{
protected:
    
    FooTest() {
    }
    
    virtual ~FooTest() {
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


TEST_F(FooTest, MethodBarDoesAbc)
{
    
    //Foo f;
    EXPECT_EQ(0, 0);
}

TEST_F(FooTest, DoesXyz)
{
    
    ASSERT_TRUE(true);
}

TEST_F(FooTest, HelloWorld)
{
    float x = 2+3;
    EXPECT_EQ(x, 5);
}


int main(int argc, char **argv)
{
	cout << "This was compiled with Cmake" << endl;
    ::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
