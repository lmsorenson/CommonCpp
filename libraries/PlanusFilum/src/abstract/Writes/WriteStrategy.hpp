// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../DataStructures/AbstractDataStructure.hpp"


class WriteStrategy
{
    // virtual void parse() = 0;
public:
    AbstractDataStructure run(const char * path);
};