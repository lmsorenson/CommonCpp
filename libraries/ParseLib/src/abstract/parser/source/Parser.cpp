// Copyright 2020 Lucas Sorenson, All rights reserved.
#include "../Parser.hpp"
#include <iostream>

using ::sdg::Parser;
using ::std::cout;
using ::std::endl;
using ::std::shared_ptr;
using ::std::string;





void Parser::receive_event()
{
    this->parse();
}


void Parser::parse()
{
    while ( this->ready() && this->source_->tokens_available() )
    {   
        std::string token = source_->pull_token();
        cout << "FROM PARSER: " << token << endl;
        
    }
}

