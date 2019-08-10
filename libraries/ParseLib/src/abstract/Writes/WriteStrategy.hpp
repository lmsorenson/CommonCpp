// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../DataStructures/plDataSet.hpp"


class WriteStrategy
{
    // virtual void parse() = 0;
public:
    plDataSet run(const char * path);
};