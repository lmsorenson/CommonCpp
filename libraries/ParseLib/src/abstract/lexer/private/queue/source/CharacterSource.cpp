// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../CharacterSource.hpp"
#include <iostream>
#include <utility>

using ::sdg::CharacterSource;
using ::sdg::pipeline::Stream;
using ::std::string;

CharacterSource::CharacterSource(Stream<char> * stream)
: character_stream_(stream)
{}

bool CharacterSource::characters_available() const
{
    return !character_stream_->is_empty();
}

char CharacterSource::pull_char()
{
    return character_stream_->get_element();
}