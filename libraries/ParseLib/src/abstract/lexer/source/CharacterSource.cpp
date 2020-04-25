// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../private/CharacterSource.hpp"
#include <iostream>
#include <utility>

using ::std::string;
using ::sdg::CharacterSource;



bool CharacterSource::characters_available() const
{
    return !character_stream_->is_empty();
}

char CharacterSource::pull_char()
{
    return character_stream_->get_element();
}