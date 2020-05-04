// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include "../../intermediate/Stream.hpp"

namespace sdg {

class CharacterTarget
{
    pipeline::Stream<char> * token_stream_;

public:
    CharacterTarget(pipeline::Stream<char> * stream)
    : token_stream_(stream){}
    
    ~CharacterTarget() = default;

    virtual void send_char(char ch);
};

}// namespace sdg