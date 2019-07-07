// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/Reads/ParserFilter.hpp"

class RecordFilter : public ParserFilter
{
public:
    RecordFilter();
    ~RecordFilter();

    virtual void execute() override;
    virtual const char * name() override;
};


class FieldFilter : public ParserFilter
{
public:
    FieldFilter();
    ~FieldFilter();

    virtual void execute() override;
    virtual const char * name() override;
};