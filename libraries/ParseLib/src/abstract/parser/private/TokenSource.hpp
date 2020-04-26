// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include "../../Reads/Streams/Stream.hpp"

namespace sdg {

class TokenSource
{

public:
    TokenSource() = default;
    ~TokenSource() = default;

    virtual bool tokens_available() const = 0;
    virtual std::string pull_token() = 0;
};

}// namespace sdg