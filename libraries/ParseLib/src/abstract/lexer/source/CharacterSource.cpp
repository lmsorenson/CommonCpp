// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../public/CharacterSource.hpp"
#include <iostream>
#include <utility>

using ::std::string;
using ::sdg::CharacterSource;



bool CharacterSource::characters_available() const
{
    return !character_stream_->empty();
}

char CharacterSource::pull_char()
{
    char ch = std::move(character_stream_->front());
    character_stream_->pop_front();

    return ch;
}