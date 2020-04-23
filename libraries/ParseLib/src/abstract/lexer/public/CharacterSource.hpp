// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <deque>

namespace sdg {

class CharacterSource
{
    std::deque<char> * character_stream_;

public:
    CharacterSource(std::deque<char> * character_stream_ptr) 
    : character_stream_(character_stream_ptr){}

    bool characters_available() const;
    char pull_char();
};

}// namespace sdg