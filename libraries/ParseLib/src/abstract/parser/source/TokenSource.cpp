// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../private/TokenSource.hpp"
#include <iostream>
#include <utility>

using ::std::string;
using ::sdg::TokenSource;



bool TokenSource::tokens_available() const
{
    return !token_stream_->is_empty();
}

string TokenSource::pull_token()
{
    return token_stream_->get_element();
}