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


class CSVSource : public ::sdg::CharacterSource
{
public:
    CSVSource(pipeline::Stream<char> * character_source_ptr) 
    : CharacterSource(character_source_ptr){}
};

class CSVTarget : public ::sdg::TokenTarget
{
public:
    CSVTarget(pipeline::Stream<std::string> * token_stream_ptr) 
    : TokenTarget(token_stream_ptr){}
};

class CSVTokenSource : public ::sdg::TokenSource
{
public:
    CSVTokenSource(pipeline::Stream<std::string> * character_source_ptr) 
    : TokenSource(character_source_ptr){}
};

}// namespace csv
}// namespace sdg