// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../data/structures/node.hpp"
#include <objects/data_set.hpp>
#include <vector>


using sdg::plNode;


class ParserOutput
{
public:
    virtual void execute(std::shared_ptr<plNode>& text, sdg::DataSet& data_store) = 0;
};
