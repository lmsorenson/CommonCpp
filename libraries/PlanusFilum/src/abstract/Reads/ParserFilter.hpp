// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once







class ParserFilter
{
public:
    ParserFilter();
    ~ParserFilter();

    virtual void execute() = 0;
    virtual const char * name();
};