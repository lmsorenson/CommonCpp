// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "test_lexer_filters.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include "../../../../src/abstract/lexer/Lexer.hpp"

using std::string;
using std::vector;
using std::pair;
using std::shared_ptr;
using sdg::TokenFilter;
using ::std::cout;
using ::std::endl;




//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
sdg::test::TestFilter::TestFilter(Lexer * owner, std::string new_filter_id) 
: TokenFilter(owner, new_filter_id)
{}

bool sdg::test::TestFilter::execute(char ch)
{
    if(is_a_delimiter(ch))
    {
        stream_token();
        return true;
    }
    else
    {
        return false;
    }
}

bool sdg::test::TestFilter::is_a_delimiter(char ch)
{
    return (ch=='\n' || ch=='\r');
}