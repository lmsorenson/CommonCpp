// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "node.hpp"





class ParserFilter
{
    std::string id;

public:
    ParserFilter(std::string new_filter_id);
    ~ParserFilter();

    virtual std::vector<node> execute(const char * text) = 0;
    virtual const char * name();

    std::string GetID(int index);
};