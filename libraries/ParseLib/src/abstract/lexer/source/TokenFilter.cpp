// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../private/TokenFilter.hpp"
#include <iostream>
#include "../Lexer.hpp"

using ::std::string;
using ::std::pair;
using ::std::to_string;
using ::std::cout;
using ::std::endl;
using ::sdg::TokenFilter;
using ::sdg::ChildTokenFilter;

TokenFilter::TokenFilter(Lexer * owner, std::string new_filter_id)
: filter_id_(new_filter_id)
, owner_(owner) {}


bool TokenFilter::is_cache_empty()
{
    if(owner_)
        return owner_->is_buffer_empty();
    else
        return true;
}

char TokenFilter::last_delimiter()
{
    if(owner_)
        return owner_->last_delimiter();
    else
        return '\0';
}

void TokenFilter::stream_token()
{
    if(owner_)
        owner_->produce_token(filter_id_);
}

void TokenFilter::stream_tagged_token()
{
    if(owner_)
        owner_->produce_tagged_token(pair<string, string>(filter_id_ + "(", ")"));

    
}

void TokenFilter::notify_error(Error error)
{
    cout << "Error(" << error.code << ")" << endl;

    if(owner_)
        owner_->handle_error(error);
}


ChildTokenFilter::ChildTokenFilter(Lexer * owner, std::string new_filter_id, TokenFilter * parent_filter)
: parent_(parent_filter)
, TokenFilter(owner, new_filter_id) {}