// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../../../src/abstract/lexer/Lexer.hpp"


namespace sdg {
namespace test {




class TestFilter : public ::sdg::TokenFilter
{
public:
    TestFilter( Lexer *  owner, std::string a_filter_id );
    ~TestFilter()=default;

    virtual bool execute(char ch) override;
    virtual bool is_a_delimeter(char ch) override;
};



class FieldTokenFilter : public ::sdg::ChildTokenFilter
{
public:
    FieldTokenFilter( Lexer * owner, std::string a_filter_id, TokenFilter * parent_filter );
    ~FieldTokenFilter()=default;

    virtual bool execute( char ch ) override;
    virtual bool is_a_delimeter( char ch ) override;
};



class TestSource : public ::sdg::CharacterSource
{
public:
    TestSource( pipeline::Stream<char> * character_source_ptr ) 
    : CharacterSource( character_source_ptr ){}
};



class TestTarget : public ::sdg::TokenTarget
{
public:
    TestTarget( std::deque<std::string> * token_stream_ptr ) 
    : TokenTarget( token_stream_ptr){}
};



}// namespace test
}// namespace sdg