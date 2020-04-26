// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <deque>
#include "../../Reads/Streams/Stream.hpp"


namespace sdg {

class CharacterSource
{
public:
    CharacterSource() = default;
    ~CharacterSource() = default;

    virtual bool characters_available() const = 0;
    virtual char pull_char() = 0;
};

}// namespace sdg