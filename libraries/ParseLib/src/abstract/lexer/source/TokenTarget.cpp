// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../private/TokenTarget.hpp"
#include <iostream>

using ::std::string;
using ::sdg::TokenTarget;

void TokenTarget::send_token( std::string a_new_token )
{
    token_stream_->add( a_new_token );
}