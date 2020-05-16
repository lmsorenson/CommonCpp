// Copyright 2020 Lucas Sorenson, All rights reserved.
#include "../Lexer.hpp"

#include "../shape/LexerState.hpp"
#include "../shape/dependent_entity/state/PendingState.hpp"
#include <iostream>
#include <time.h> 

using ::sdg::Lexer;
using ::sdg::PendingState;
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

    while ( this->ready() && this->source_->characters_available() )
    {   
        bool should_buffer = false;
        char ch = source_->pull_char();

        if(shape_)
        {
            shape_->run(should_buffer, ch);
        }
        else
        {
            cout << "error: no initial state.";
        }

        if( should_buffer )
            buffer_.append( string(1, ch) );
    }

    stopwatch_.stop();
}


double Lexer::get_time() const
{
    return stopwatch_.read_seconds();
}

void Lexer::produce_token()
{
    if (!buffer_.empty() )
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
    target_->send_token(token_content);
    stopwatch_.start();
}


void Lexer::produce_tagged_token(std::pair<std::string, std::string> tag)
{
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
}


void Lexer::handle_error(Error error)
{
    error_queue_->add_error(error);
}

bool Lexer::is_buffer_empty()
{
    return buffer_.empty();
}

