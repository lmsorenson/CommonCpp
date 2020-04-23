// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../public/TokenTarget.hpp"
#include <iostream>

using ::std::string;
using ::sdg::TokenTarget;

void TokenTarget::send_token(std::string a_new_token)
{
    token_stream_->push_back(a_new_token);
}