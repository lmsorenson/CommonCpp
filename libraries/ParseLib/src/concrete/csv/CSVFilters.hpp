// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/Reads/ParserFilter.hpp"
#include "../../abstract/Reads/ParserOutput.hpp"

class HeaderFilter : public ParserFilter
{
public:
    HeaderFilter(std::string new_filter_id);
    ~HeaderFilter();

    int32_t execute(std::string text, std::vector<node>& output) override;
    virtual std::string name() override;
};

class RecordFilter : public ParserFilter
{
public:
    RecordFilter(std::string new_filter_id);
    ~RecordFilter();

    int32_t execute(std::string text, std::vector<node>& output) override;
    virtual std::string name() override;
};


class FieldFilter : public ParserFilter
{
    int32_t field_count;

public:
    FieldFilter(std::string new_filter_id);
    ~FieldFilter();

    virtual int32_t execute(std::string text, std::vector<node>& output) override;
    virtual std::string name() override;
    bool IsFieldCountValid(int32_t field_count_param);
};


class CSVOutput : public ParserOutput
{
    virtual void execute(std::shared_ptr<node>& text, plDataSet& data_store) override;
};