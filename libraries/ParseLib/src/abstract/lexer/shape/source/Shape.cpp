// Copyright 2020 Lucas Sorenson, All rights reserved.
#include <iostream>
#include <string>
#include "../Shape.hpp"
#include "../../Lexer.hpp"

using ::sdg::Shape;
using ::std::pair;
using ::std::string;
using ::std::cout;
using ::std::endl;



void Shape::init()
{
    current_state_->initialize();
    is_initialized_ = true;
}

void Shape::run(bool &should_buffer, char ch)
{
    if (this->ready() && !this->is_initialized_)
    {
        this->init();
    }
        

    if( this->ready() )
    {
        current_state_->perform_scan(ch);
        current_state_->should_buffer(should_buffer, ch);
    }
    else
    {
        cout << "shape error: shape is not properly configured to process characters." << endl;
        context_->handle_error({UNKNOWN_ERROR});
    }
}

void Shape::generate_token(string token) const
{
    context_->produce_token(token);
}

void Shape::generate_token(std::pair<std::string, std::string> bracket)
{
    context_->produce_tagged_token( pair(bracket.first, bracket.second) );
}

void Shape::handle_error(Error error)
{
    context_->handle_error(error);
}