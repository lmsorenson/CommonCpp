// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "ParserFilter.hpp"
#include "ParserOutput.hpp"




class ParserPipeline
{
    std::vector<std::shared_ptr<ParserFilter>> filters;
    std::shared_ptr<ParserOutput> output;
    
public:
    ParserPipeline();
    ~ParserPipeline();

    int32_t AddFilter(std::shared_ptr<ParserFilter> filter);
    int32_t AddOutput(std::shared_ptr<ParserOutput> output);
    void execute(std::vector<std::string> text);
};