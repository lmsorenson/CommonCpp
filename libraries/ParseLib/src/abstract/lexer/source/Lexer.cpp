// Copyright 2020 Lucas Sorenson, All rights reserved.
#include "../Lexer.hpp"
#include <iostream>

using ::sdg::Lexer;
using ::std::cout;
using ::std::endl;
using ::std::shared_ptr;






void Lexer::accept_char(char ch)
{
    bool flush_token;

    for(int i=(filters_.size()-1); i >= 0; --i)
        flush_token = (filters_[i]->execute(ch) || flush_token);

    if(!flush_token)
        buffer_.append(std::string(1, ch));
}

void Lexer::produce_token()
{
    if(!buffer_.empty() && (previous_token_.compare(buffer_)!=0 && !bAllowDuplicates_))
    {
        previous_token_.clear();
        previous_token_.append(buffer_);
        buffer_.clear();

        cout << " " << previous_token_ << " ";
    }
}

void Lexer::produce_token(std::string token_content)
{
    if(previous_token_.compare(token_content)!=0 && !bAllowDuplicates_)
    {
        previous_token_.clear();
        previous_token_.append(token_content);

        cout << " " << previous_token_ << " ";
    }
}

void Lexer::produce_tagged_token(std::pair<std::string, std::string> tag)
{
    if(!buffer_.empty() && (previous_token_.compare(buffer_)!=0 && !bAllowDuplicates_))
    {
        previous_token_.clear();
        previous_token_
        .append(tag.first)
        .append(buffer_)
        .append(tag.second);
        buffer_.clear();

        cout << " " << previous_token_ << " ";
        
    }
}