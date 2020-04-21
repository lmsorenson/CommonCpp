// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "csv_token_filters.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include "../../abstract/lexer/Lexer.hpp"

using std::string;
using std::vector;
using std::pair;
using std::shared_ptr;
using sdg::TokenFilter;
using sdg::csv::HeaderTokenFilter;
using ::std::cout;
using ::std::endl;



//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
HeaderTokenFilter::HeaderTokenFilter(Lexer * owner, std::string new_filter_id) 
: TokenFilter(owner, new_filter_id)
{}

bool HeaderTokenFilter::execute(char ch)
{
    return false;
}

bool sdg::csv::HeaderTokenFilter::is_a_delimeter(char ch)
{
    return (false);
}


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
sdg::csv::RecordTokenFilter::RecordTokenFilter(Lexer * owner, std::string new_filter_id) 
: TokenFilter(owner, new_filter_id)
{}

bool sdg::csv::RecordTokenFilter::execute(char ch)
{
    if(is_a_delimeter(ch))
    { 
        owner_->produce_token(filter_id_);
        return true;
    }
    else
    {
        return false;
    }
}

bool sdg::csv::RecordTokenFilter::is_a_delimeter(char ch)
{
    return (ch=='\n' || ch=='\r');
}


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
sdg::csv::FieldTokenFilter::FieldTokenFilter(Lexer * owner, std::string new_filter_id, TokenFilter * parent_filter) 
: ChildTokenFilter(owner, new_filter_id, parent_filter)
{}

bool sdg::csv::FieldTokenFilter::execute(char ch)
{
    if( is_a_delimeter(ch) || parent_->is_a_delimeter(ch) )
    {
        owner_->produce_tagged_token(pair<string, string>(filter_id_ + "(", ")"));
        return true;
    }
    else
    {
        return false;
    }
    
}

bool sdg::csv::FieldTokenFilter::is_a_delimeter(char ch)
{
    return (ch==',');
}

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
void sdg::csv::CSVTarget::execute(string token)
{
}