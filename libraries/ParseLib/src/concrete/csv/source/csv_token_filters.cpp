// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../csv_token_filters.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include "../../../abstract/lexer/Lexer.hpp"

using sdg::TokenFilter;
using ::sdg::csv::FieldToken;
using sdg::csv::FieldTokenFilter;
using sdg::csv::HeaderTokenFilter;
using ::sdg::csv::RecordToken;
using sdg::csv::RecordTokenFilter;
using ::std::cout;
using ::std::endl;
using std::shared_ptr;
using std::string;
using std::vector;

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
HeaderTokenFilter::HeaderTokenFilter(Lexer *owner, std::string new_filter_id)
    : TokenFilter(owner, new_filter_id)
{
}

bool HeaderTokenFilter::execute(char ch)
{
    return false;
}

bool HeaderTokenFilter::is_a_delimiter(char ch)
{
    return (false);
}

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
RecordTokenFilter::RecordTokenFilter(Lexer *owner, std::string new_filter_id)
    : TokenFilter(owner, new_filter_id)
{
}

bool RecordTokenFilter::execute(char ch)
{
    if (is_a_delimiter(ch))
    {
        stream_token();

        return true;
    }
    else
    {
        return false;
    }
}

bool RecordTokenFilter::is_a_delimiter(char ch)
{
    return (ch == '\n' || ch == '\r');
}

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
FieldTokenFilter::FieldTokenFilter(Lexer *owner, std::string new_filter_id, TokenFilter *parent_filter)
    : ChildTokenFilter(owner, new_filter_id, parent_filter)
{
}

bool FieldTokenFilter::execute(char ch)
{
    if (is_a_delimiter(ch))
    {
        stream_tagged_token();
        return true;
    }
    else if (parent_->is_a_delimiter(ch))
    {
        //if there have been no characters cached since the last
        //comma delimiter the record ends on a comma
        if (is_cache_empty() && is_a_delimiter(last_delimiter()))
        {
            notify_error({FORMAT_ERROR});
            return false;
        }

        stream_tagged_token();
        return true;
    }
    else
    {
        return false;
    }
}

bool FieldTokenFilter::is_a_delimiter(char ch)
{
    return (ch == ',');
}

bool RecordToken::classify(std::string token)
{
    if (token.compare(type_id_) == 0)
    {
        char rec_buffer[10];
        sprintf(rec_buffer, "R%d", get_count()); // important to increment before

        owner_->produce_node(rec_buffer, string());

        return true;
    }

    return false;
}

bool FieldToken::classify(std::string token)
{

    if (token.substr(0, 1).compare(type_id_) == 0 && parent_)
    {
        char buffer[10];
        sprintf(buffer, "R%d-F%d", parent_->get_count(), get_count());

        owner_->produce_child_node({parent_->get_count()}, buffer, token.substr(token.find("(") + 1, token.length() - (token.find("(") + 2)));

        return true;
    }

    return false;
}
