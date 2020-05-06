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

    virtual bool execute(char ch, int *error_code=nullptr ) override;
    virtual bool is_a_delimiter(char ch) override;
};



class FieldTokenFilter : public ::sdg::ChildTokenFilter
{
public:
    FieldTokenFilter( Lexer * owner, std::string a_filter_id, TokenFilter * parent_filter );
    ~FieldTokenFilter()=default;

    virtual bool execute( char ch, int *error_code=nullptr ) override;
    virtual bool is_a_delimiter( char ch ) override;
};



}// namespace test
}// namespace sdg