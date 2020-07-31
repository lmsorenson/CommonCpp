// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/Reads/ParserFilter.hpp"
#include "../../abstract/Reads/ParserOutput.hpp"


namespace sdg {
namespace csv {

class HeaderFilter : public ::sdg::ParserFilter
{
public:
    HeaderFilter(const std::string &new_filter_id);
    virtual ~HeaderFilter()=default;

    virtual int32_t execute(const std::string &text, std::vector<sdg::SyntaxNode>& output) override;
    virtual int32_t inverse(std::vector<std::string> string_set, std::string &compiled_string) override;
    virtual std::string name() override;
};

class RecordFilter : public ::sdg::ParserFilter
{
public:
    RecordFilter(const std::string &new_filter_id);
    virtual ~RecordFilter()=default;

    virtual int32_t execute(const std::string &text, std::vector<sdg::SyntaxNode>& output) override;
    virtual int32_t inverse(std::vector<std::string> string_set, std::string &compiled_string) override;
    virtual std::string name() override;
};


class FieldFilter : public ::sdg::ParserFilter
{
    int32_t field_count;

public:
    FieldFilter(const std::string &new_filter_id);
    virtual ~FieldFilter()=default;

    virtual int32_t execute(const std::string &ext, std::vector<sdg::SyntaxNode>& output) override;
    virtual int32_t inverse(std::vector<std::string> string_set, std::string &compiled_string) override;
    virtual std::string name() override;
    bool IsFieldCountValid(int32_t field_count_param);
};


class CSVOutput : public ::sdg::ParserOutput
{
    virtual void execute(std::shared_ptr<sdg::SyntaxNode>& text, sdg::DataSet& data_store) override;
};

}// namespace csv
}// namespace sdg