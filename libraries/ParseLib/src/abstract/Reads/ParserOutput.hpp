// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../data/structures/plNode.hpp"
#include "../../../include/plDataSet.hpp"
#include <vector>

class ParserOutput
{
public:
    virtual void execute(std::shared_ptr<plNode>& text, plDataSet& data_store) = 0;
};