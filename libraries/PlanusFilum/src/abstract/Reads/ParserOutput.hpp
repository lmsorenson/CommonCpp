// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "node.hpp"
#include <vector>

class ParserOutput
{
public:
    virtual void execute(std::shared_ptr<node>& text) = 0;
};