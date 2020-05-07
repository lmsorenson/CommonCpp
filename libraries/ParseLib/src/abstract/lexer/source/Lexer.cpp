// Copyright 2020 Lucas Sorenson, All rights reserved.
#include "../Lexer.hpp"
#include <iostream>
#include <time.h> 

using ::sdg::Lexer;
using ::std::cout;
using ::std::endl;
using ::std::shared_ptr;
using ::std::string;




void Lexer::receive_event()
{
    this->scan();
}


void Lexer::scan()
{
    stopwatch_.start();

    while ( this->ready() && this->source_->characters_available() )
    {   
        bool flush_token = 0;

        char ch = source_->pull_char();

        for( int i=(filters_.size()-1); i >= 0; --i )
            flush_token = (filters_[i]->execute(ch) || flush_token);

        if( !flush_token )
            buffer_.append( string(1, ch) );
        else
            previous_delimiter_ = ch;
    }

    stopwatch_.stop();
}


double Lexer::get_time() const
{
    return stopwatch_.read_seconds();
}


void Lexer::produce_token()
{
    if (!buffer_.empty() && (previous_token_.compare(buffer_)!=0 && !bAllowDuplicates_))
    {
        previous_token_.clear();
        previous_token_.append(buffer_);

        stopwatch_.stop();
        target_->send_token(buffer_);
        stopwatch_.start();

        buffer_.clear();
    }
}


void Lexer::produce_token(std::string token_content)
{
    if(previous_token_.compare(token_content)!=0 && !bAllowDuplicates_)
    {
        previous_token_.clear();
        previous_token_.append(token_content);

        stopwatch_.stop();
        target_->send_token(previous_token_);
        stopwatch_.start();
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

        stopwatch_.stop();
        target_->send_token(previous_token_);
        stopwatch_.start();
    }
}


void Lexer::handle_error(Error error)
{
    error_queue_->add_error(error);
}

bool Lexer::is_buffer_empty()
{
    return buffer_.empty();
}

char Lexer::last_delimiter()
{
    return previous_delimiter_;
}