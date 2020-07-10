// Copyright 2020 Lucas Sorenson, All rights reserved.
#include "../Lexer.hpp"

#include "shape/LexerState.hpp"
#include <iostream>
#include <time.h> 

#include "../public/DependentEntity.hpp"

using ::sdg::Lexer;
using ::std::cout;
using ::std::endl;
using ::std::shared_ptr;
using ::std::dynamic_pointer_cast;
using ::std::string;




void Lexer::receive_event()
{
    this->scan();
}


void Lexer::scan()
{
    stopwatch_.start();

    while (this->ready() && this->source_->characters_available() && !shape_->is_complete())
    {   
        bool should_buffer = false;
        char ch = source_->pull_char();

        shape_->run(should_buffer, ch);

        if( should_buffer )
            buffer_.append( string(1, ch) );
    }

    if (this->ready() && shape_ && shape_->is_complete())
        shape_->transition();

    stopwatch_.stop();
}


double Lexer::get_time() const
{
    return stopwatch_.read_seconds();
}

void Lexer::produce_token()
{
    if ( !buffer_.empty() )
    {
        stopwatch_.stop();
        target_->send_token(buffer_);
        stopwatch_.start();

        buffer_.clear();
    }
}


void Lexer::produce_token(std::string token_content)
{
    stopwatch_.stop();
    if (target_)
        target_->send_token(token_content);
    stopwatch_.start();
}


int32_t Lexer::produce_tagged_token(std::pair<std::string, std::string> tag)
{
    int32_t buffer_size = buffer_.size();

    if(!buffer_.empty())
    {
        std::string token;

        token
        .append(tag.first)
        .append(buffer_)
        .append(tag.second);

        buffer_.clear();

        stopwatch_.stop();
        target_->send_token(token);
        stopwatch_.start();
    }
    
    return buffer_size;
}


void Lexer::handle_error(Error error)
{
    if (error_queue_)
        error_queue_->add_error(error);
}

bool Lexer::is_buffer_empty()
{
    return buffer_.empty();
}