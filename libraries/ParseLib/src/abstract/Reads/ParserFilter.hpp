// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "../data/structures/plNode.hpp"


/* Each element/entity output by the filter is identified using the format:
    label + index
     */
class ParserFilter
{
    std::string label;

public:
    ParserFilter(std::string new_filter_id);
    ~ParserFilter();

    virtual int32_t execute(std::string text, std::vector<plNode> & output) = 0;
    virtual int32_t inverse(std::vector<std::string> vector, std::string &compiled_string) = 0;
    virtual std::string name();

    std::string GetID(int index);
    std::string GetLabel();

    enum : int32_t
    {
        FILTER_SUCCESS=0,
        FILTER_FORMAT_ERROR,
        FILTER_UNKNOWN_ERROR
    };
};