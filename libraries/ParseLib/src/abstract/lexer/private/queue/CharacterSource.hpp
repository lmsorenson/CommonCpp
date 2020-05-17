// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <deque>
#include "../../../intermediate/Stream.hpp"


namespace sdg {

class CharacterSource
{
    pipeline::Stream<char> * character_stream_;

public:
    CharacterSource(pipeline::Stream<char> * stream)
    : character_stream_(stream){}

    ~CharacterSource() = default;

    virtual bool characters_available() const;
    virtual char pull_char();
};

}// namespace sdg