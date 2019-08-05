// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../DataStructures/InstanceSet.hpp"


class WriteStrategy
{
    // virtual void parse() = 0;
public:
    InstanceSet run(const char * path);
};