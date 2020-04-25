// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <deque>
#include "../../Reads/Stream.hpp"

namespace sdg {

class CharacterSource
{
    pipeline::Stream<char> * character_stream_;

public:
    CharacterSource( pipeline::Stream<char> * shared_queue_ptr ) 
    : character_stream_( shared_queue_ptr ){}

    bool characters_available() const;
    char pull_char();
};

}// namespace sdg