// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../private/CharacterTarget.hpp"



using ::std::string;
using ::sdg::CharacterTarget;


CharacterTarget::CharacterTarget(pipeline::Stream<char> * stream)
: token_stream_(stream)
{}

void CharacterTarget::send_char( char ch )
{
    token_stream_->add( ch );
}