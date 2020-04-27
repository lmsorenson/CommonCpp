// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../private/TokenSource.hpp"


using ::sdg::TokenSource;
using ::std::string;



bool TokenSource::tokens_available() const
{
    return !token_stream_->is_empty();
}

string TokenSource::pull_token()
{
    return token_stream_->get_element();
}