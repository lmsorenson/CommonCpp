// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/lexer/public/TokenFilter.hpp"
#include "../../abstract/lexer/public/TokenTarget.hpp"


namespace sdg {
namespace csv {

class HeaderTokenFilter : public ::sdg::TokenFilter
{
public:
    HeaderTokenFilter(Lexer *  owner, std::string a_filter_id);
    ~HeaderTokenFilter()=default;

    virtual bool execute(char ch) override;
    virtual bool is_a_delimeter(char ch) override;
    // virtual std::string name() override;
};

class RecordTokenFilter : public ::sdg::TokenFilter
{
public:
    RecordTokenFilter(Lexer * owner, std::string a_filter_id);
    ~RecordTokenFilter()=default;

    virtual bool execute(char ch) override;
    virtual bool is_a_delimeter(char ch) override;
    // virtual std::string name() override;
};


class FieldTokenFilter : public ::sdg::ChildTokenFilter
{
public:
    FieldTokenFilter(Lexer * owner, std::string a_filter_id, TokenFilter * parent_filter);
    ~FieldTokenFilter()=default;

    virtual bool execute(char ch) override;
    virtual bool is_a_delimeter(char ch) override;
    // virtual std::string name() override;
};


class CSVTarget : public ::sdg::TokenTarget
{
    virtual void execute(std::string token) override;
};

}// namespace csv
}// namespace sdg