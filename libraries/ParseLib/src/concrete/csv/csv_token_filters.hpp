// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/lexer/Lexer.hpp"
#include "../../abstract/parser/Parser.hpp"

namespace sdg {
namespace csv {


class HeaderTokenFilter : public ::sdg::TokenFilter
{
public:
    HeaderTokenFilter(Lexer *  owner, std::string a_filter_id);
    ~HeaderTokenFilter()=default;

    virtual bool execute(char ch, int *error_code = nullptr) override;
    virtual bool is_a_delimiter(char ch) override;
};



class RecordTokenFilter : public ::sdg::TokenFilter
{
public:
    RecordTokenFilter(Lexer * owner, std::string a_filter_id);
    ~RecordTokenFilter()=default;

    virtual bool execute(char ch, int *error_code = nullptr) override;
    virtual bool is_a_delimiter(char ch) override;
};



class FieldTokenFilter : public ::sdg::ChildTokenFilter
{
public:
    FieldTokenFilter(Lexer * owner, std::string a_filter_id, TokenFilter * parent_filter);
    ~FieldTokenFilter()=default;

    virtual bool execute(char ch, int *error_code = nullptr) override;
    virtual bool is_a_delimiter(char ch) override;
};



class RecordToken : public ::sdg::CollectionToken
{
public:
    RecordToken(Parser *parser, std::string new_type_id) 
    : CollectionToken(parser, new_type_id){}

    virtual bool classify(std::string token) override;
};



class FieldToken : public ::sdg::TokenType
{
public:
    FieldToken(Parser *parser, std::string new_type_id, TokenType *parent_token) 
    : TokenType(parser, new_type_id, parent_token){}

    virtual bool classify(std::string token) override;
};


}// namespace csv
}// namespace sdg