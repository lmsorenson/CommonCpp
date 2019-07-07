// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>






class ParserFilter
{
public:
    ParserFilter();
    ~ParserFilter();

    virtual std::vector<std::string> execute(const char * text) = 0;
    virtual const char * name();
};