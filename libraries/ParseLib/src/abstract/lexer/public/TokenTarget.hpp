// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>

namespace sdg {

class TokenTarget
{
public:
    virtual void execute(std::string token) = 0;
};

}// namespace sdg