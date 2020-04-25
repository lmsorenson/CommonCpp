#include <string>
#include <iostream>
#include <deque>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "../../TestFramework.hpp"
#include "../../../../src/abstract/lexer/Lexer.hpp"
#include "../../../../src/abstract/Reads/Stream.hpp"
#include "test_lexer_filters.hpp"

using sdg::Lexer;
using std::deque;
using sdg::pipeline::Stream;
using std::string;
using sdg::test::TestSource;
using sdg::test::TestFilter;
using sdg::test::TestTarget;

class LexerComponentTests : public ::testing::Test
{

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


TEST_F(LexerComponentTests, normal_filter_successful )
{
    Lexer lexer;
    
    Stream<char> source_stream;
    deque<string> target_stream;

    //configure
    lexer.set_source<TestSource>( &source_stream );
    lexer.add_filter<TestFilter>("F");
    lexer.set_target<TestTarget>( &target_stream );

    for(int i=0; i<5 ;++i)
    {
        source_stream.add('B');
    }

    source_stream.add('\r');


    ASSERT_EQ( target_stream.front(), string("BBBBB") );
}

TEST_F(LexerComponentTests, add_content_with_no_components )
{
    Lexer lexer;
    
    Stream<char> source_stream;
    deque<string> target_stream;

    for(int i=0; i<5 ;++i)
    {
        source_stream.add('B');
    }

    source_stream.add('\r');

    ASSERT_EQ( target_stream.size(), 0 );
}

TEST_F(LexerComponentTests, configure_source_after_adding_content )
{
    Lexer lexer;
    
    Stream<char> source_stream;
    deque<string> target_stream;

    for(int i=0; i<5 ;++i)
    {
        source_stream.add('B');
    }

    source_stream.add('\r');

    //configure
    lexer.set_source<TestSource>( &source_stream );
    lexer.add_filter<TestFilter>("F");
    lexer.set_target<TestTarget>( &target_stream );

    ASSERT_EQ( target_stream.front(), string("BBBBB") );
}

TEST_F(LexerComponentTests, configure_source_and_target_after_filters )
{
    Lexer lexer;
    
    Stream<char> source_stream;
    deque<string> target_stream;

    for(int i=0; i<5 ;++i)
    {
        source_stream.add('B');
    }

    source_stream.add('\r');

    //configure
    lexer.add_filter<TestFilter>("F");
    lexer.set_source<TestSource>( &source_stream );
    lexer.set_target<TestTarget>( &target_stream );

    ASSERT_EQ( target_stream.front(), string("BBBBB") );
}