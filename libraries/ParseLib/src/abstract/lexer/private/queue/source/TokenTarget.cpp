// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../TokenTarget.hpp"
#include <iostream>


using ::std::string;
using ::sdg::TokenTarget;
using ::std::cout;
using ::std::endl;


void TokenTarget::send_token( string a_new_token )
{
    cout << "Lexer produced token: " << a_new_token << endl;
    token_stream_->add( a_new_token );
}