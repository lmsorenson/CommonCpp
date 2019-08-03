// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/Reads/ParserFilter.hpp"
#include "../../abstract/Reads/ParserOutput.hpp"

class HeaderFilter : public ParserFilter
{
public:
    HeaderFilter(std::string new_filter_id);
    ~HeaderFilter();

    std::vector<node> execute(std::string text) override;
    virtual std::string name() override;
};

class RecordFilter : public ParserFilter
{
public:
    RecordFilter(std::string new_filter_id);
    ~RecordFilter();

    std::vector<node> execute(std::string text) override;
    virtual std::string name() override;
};


class FieldFilter : public ParserFilter
{
public:
    FieldFilter(std::string new_filter_id);
    ~FieldFilter();

    virtual std::vector<node> execute(std::string text) override;
    virtual std::string name() override;
};


class CSVOutput : public ParserOutput
{
    virtual void execute(std::shared_ptr<node>& text, AbstractDataStructure& data_store) override;
};