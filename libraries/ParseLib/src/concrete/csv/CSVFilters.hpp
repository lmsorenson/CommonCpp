// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/Reads/ParserFilter.hpp"
#include "../../abstract/Reads/ParserOutput.hpp"





class HeaderFilter : public ::sdg::ParserFilter
{
public:
    HeaderFilter(std::string new_filter_id);
    ~HeaderFilter()=default;

    virtual int32_t execute(std::string text, std::vector<sdg::plNode>& output) override;
    virtual int32_t inverse(std::vector<std::string> string_set, std::string &compiled_string) override;
    virtual std::string name() override;
};

class RecordFilter : public ::sdg::ParserFilter
{
public:
    RecordFilter(std::string new_filter_id);
    ~RecordFilter()=default;

    virtual int32_t execute(std::string text, std::vector<sdg::plNode>& output) override;
    virtual int32_t inverse(std::vector<std::string> string_set, std::string &compiled_string) override;
    virtual std::string name() override;
};


class FieldFilter : public ::sdg::ParserFilter
{
    int32_t field_count;

public:
    FieldFilter(std::string new_filter_id);
    ~FieldFilter()=default;

    virtual int32_t execute(std::string text, std::vector<sdg::plNode>& output) override;
    virtual int32_t inverse(std::vector<std::string> string_set, std::string &compiled_string) override;
    virtual std::string name() override;
    bool IsFieldCountValid(int32_t field_count_param);
};


class CSVOutput : public ::sdg::ParserOutput
{
    virtual void execute(std::shared_ptr<sdg::plNode>& text, sdg::DataSet& data_store) override;
};