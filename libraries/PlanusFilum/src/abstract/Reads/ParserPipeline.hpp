// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "ParserFilter.hpp"
#include "ParserOutput.hpp"




class ParserPipeline
{
    std::vector<std::shared_ptr<ParserFilter>> filters;
    
public:
    ParserPipeline();
    ~ParserPipeline();

    int32_t AddFilter(std::shared_ptr<ParserFilter> filter);

    void execute(const char * text);
};