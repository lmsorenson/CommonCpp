// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../intermediate/node.hpp"
#include <objects/data_set.hpp>
#include <vector>





namespace sdg {

class ParserOutput
{
public:
    virtual void execute(std::shared_ptr<sdg::SyntaxNode>& text, sdg::DataSet& data_store) = 0;
};

}// namespace sdg