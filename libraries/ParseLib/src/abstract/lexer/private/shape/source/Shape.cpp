// Copyright 2020 Lucas Sorenson, All rights reserved.
#include <iostream>
#include <string>
#include "../Shape.hpp"
#include "../../../Lexer.hpp"

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
        this->init();

    if( this->ready() )
    {
        // do
        // {
        //     //check transitions
            current_state_->perform_scan(ch);//<-- should return a transition

        //     //make transition.
        //     //this->set_state<>();
            
        // } while (/* transition found */);

        // //check if buffering the current character is allowed
        // //in this state.
        // current_state_->should_buffer(should_buffer, ch);
    }
    else
    {
        cout << "shape error: the shape is not properly configured to process characters." << endl;
        this->handle_error({UNKNOWN_ERROR});
    }
}

void Shape::generate_token(string token) const
{
    if (context_)
        context_->produce_token(token);
}

void Shape::generate_token(std::pair<std::string, std::string> bracket)
{
    if (context_)
        context_->produce_tagged_token( pair(bracket.first, bracket.second) );
}

void Shape::handle_error(Error error)
{
    if (context_)
    {
        context_->handle_error(error);
    }
}