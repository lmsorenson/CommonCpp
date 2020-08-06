#pragma once
#include <string>
#include <iostream>
#include <deque>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "../../TestFramework.hpp"
#include "../../../../src/abstract/lexer/Lexer.hpp"
#include "../../../../src/abstract/intermediate/Stream.hpp"
#include "test_lexer_filters.hpp"

using sdg::Lexer;
using std::deque;
using sdg::pipeline::Stream;
using std::string;
using sdg::TokenTarget;
using sdg::CharacterSource;
using sdg::Error;
using sdg::ErrorQueue;

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
    Stream<string> target_stream;
    Stream<Error> error_stream;

    //configure
    lexer.set_source<CharacterSource>( &source_stream );
    lexer.set_target<TokenTarget>( &target_stream );
    lexer.set_error_queue<ErrorQueue>( &error_stream );

    for(int i=0; i<5 ;++i)
    {
        source_stream.add('B');
    }

    source_stream.add('\r');

    // ASSERT_EQ( target_stream.get_element(), string("F(BBBBB)") );
}

TEST_F(LexerComponentTests, add_content_with_no_components )
{
    Lexer lexer;
    
    Stream<char> source_stream;
    Stream<string> target_stream;
    Stream<Error> error_stream;

    for(int i=0; i<5 ;++i)
    {
        source_stream.add('B');
    }

    source_stream.add('\r');

    ASSERT_EQ( target_stream.is_empty(), true );
}

TEST_F(LexerComponentTests, configure_source_after_adding_content )
{
    Lexer lexer;
    
    Stream<char> source_stream;
    Stream<string> target_stream;
    Stream<Error> error_stream;

    for(int i=0; i<5 ;++i)
    {
        source_stream.add('B');
    }

    source_stream.add('\r');

    //configure
    lexer.set_source<CharacterSource>( &source_stream );
    lexer.set_target<TokenTarget>( &target_stream );
    lexer.set_error_queue<ErrorQueue>( &error_stream );

    // ASSERT_EQ( target_stream.get_element(), string("F(BBBBB)") );
}

TEST_F(LexerComponentTests, configure_source_and_target_after_filters )
{
    Lexer lexer;
    
    Stream<char> source_stream;
    Stream<string> target_stream;
    Stream<Error> error_stream;

    for(int i=0; i<5 ;++i)
    {
        source_stream.add('B');
    }

    source_stream.add('\r');

    //configure
    lexer.set_source<CharacterSource>( &source_stream );
    lexer.set_target<TokenTarget>( &target_stream );
    lexer.set_error_queue<ErrorQueue>( &error_stream );

    // ASSERT_EQ( target_stream.get_element(), string("F(BBBBB)") );
}