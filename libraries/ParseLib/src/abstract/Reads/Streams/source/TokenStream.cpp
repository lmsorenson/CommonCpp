// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../TokenStream.hpp"


using ::sdg::CSVTarget;
using ::sdg::CSVTokenSource;
using ::std::string;


void CSVTarget::send_token( string a_new_token )
{
    token_stream_->add( a_new_token );
}

bool CSVTokenSource::tokens_available() const
{
    return !token_stream_->is_empty();
}

string CSVTokenSource::pull_token()
{
    return token_stream_->get_element();
}