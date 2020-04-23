#include <string>
#include <iostream>
#include <queue>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "../TestFramework.hpp"
#include "../../../src/abstract/lexer/Lexer.hpp"

using sdg::Lexer;
using std::queue;
using std::string;

class LexerComponentTests : public ::testing::Test
{
    Lexer lexer_;

protected:

    LexerComponentTests()
    {

    }

    virtual ~LexerComponentTests()
    {

    }

    virtual void SetUp()
    {
    }
    
    virtual void TearDown()
    {
    }
    
};


TEST_F(LexerComponentTests, Test1)
{
    Lexer lexer;
    queue<string> stream;



    ASSERT_EQ(true, false);
}