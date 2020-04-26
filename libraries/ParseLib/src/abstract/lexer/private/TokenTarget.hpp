// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include "../../Reads/Streams/Stream.hpp"

namespace sdg {

class TokenTarget
{
public:
    TokenTarget() = default;
    ~TokenTarget() = default;

    virtual void send_token(std::string) = 0;
};

}// namespace sdg