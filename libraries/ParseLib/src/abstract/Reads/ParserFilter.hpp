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

    virtual int32_t execute(std::string text, std::vector<node> & output) = 0;
    virtual std::string name();

    std::string GetID(int index);

    enum : int32_t
    {
        FILTER_SUCCESS=0,
        FILTER_FORMAT_ERROR,
        FILTER_UNKNOWN_ERROR
    };
};