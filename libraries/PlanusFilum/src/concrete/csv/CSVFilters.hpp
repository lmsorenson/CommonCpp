// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/Reads/ParserFilter.hpp"
#include "../../abstract/Reads/ParserOutput.hpp"

class RecordFilter : public ParserFilter
{
public:
    RecordFilter();
    ~RecordFilter();

    virtual std::vector<node> execute(const char * text) override;
    virtual const char * name() override;
};


class FieldFilter : public ParserFilter
{
public:
    FieldFilter();
    ~FieldFilter();

    virtual std::vector<node> execute(const char * text) override;
    virtual const char * name() override;
};


class CSVOutput : public ParserOutput
{
    virtual void execute() override;
};