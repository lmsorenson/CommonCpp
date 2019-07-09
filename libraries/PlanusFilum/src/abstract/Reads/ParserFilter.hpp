// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "node.hpp"





class ParserFilter
{
public:
    ParserFilter();
    ~ParserFilter();

    virtual std::vector<node> execute(const char * text) = 0;
    virtual const char * name();
};