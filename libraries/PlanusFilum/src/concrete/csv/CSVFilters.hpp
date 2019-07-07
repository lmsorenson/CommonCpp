// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/Reads/ParserFilter.hpp"

class RecordFilter : public ParserFilter
{
public:
    RecordFilter();
    ~RecordFilter();

    virtual std::vector<std::string> execute(const char * text) override;
    virtual const char * name() override;
};


class FieldFilter : public ParserFilter
{
public:
    FieldFilter();
    ~FieldFilter();

    virtual std::vector<std::string> execute(const char * text) override;
    virtual const char * name() override;
};