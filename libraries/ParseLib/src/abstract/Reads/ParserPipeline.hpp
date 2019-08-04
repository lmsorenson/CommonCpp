// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include <string>
#include "ParserFilter.hpp"
#include "ParserOutput.hpp"
#include "node.hpp"
#include "../DataStructures/AbstractDataStructure.hpp"


class ParserPipeline
{
    std::vector<std::shared_ptr<ParserFilter>> filters;
    std::shared_ptr<ParserOutput> output;
    
public:
    ParserPipeline();
    ~ParserPipeline();

    int32_t add_filter(std::shared_ptr<ParserFilter> filter);
    int32_t add_output(std::shared_ptr<ParserOutput> output);
    int32_t execute(std::shared_ptr<node>& text, AbstractDataStructure& data_store);

    enum : int32_t
    {
        PIPELINE_SUCCESS=0,
        PIPELINE_FORMAT_ERROR,
        PIPELINE_UNKNOWN_ERROR
    };
};