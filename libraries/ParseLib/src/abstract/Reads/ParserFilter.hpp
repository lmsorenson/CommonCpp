// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "../intermediate/node.hpp"



namespace sdg {
/* Each element/entity output by the filter is identified using the format:
    label + index
     */
class ParserFilter
{
    std::string label;

public:
    ParserFilter(const std::string &new_filter_id);
    virtual ~ParserFilter();

    virtual int32_t execute(const std::string &text, std::vector<sdg::SyntaxNode> & output) = 0;
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

}// namespace sdg