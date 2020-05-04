// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../private/CharacterTarget.hpp"



using ::std::string;
using ::sdg::CharacterTarget;


void CharacterTarget::send_char( char ch )
{
    token_stream_->add( ch );
}