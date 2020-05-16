// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/lexer/Lexer.hpp"
#include "../../abstract/parser/Parser.hpp"

namespace sdg {
namespace csv {


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