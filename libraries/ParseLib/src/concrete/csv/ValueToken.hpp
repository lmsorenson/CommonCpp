// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/parser/public/TokenType.hpp"
#include "../../abstract/parser/public/DependentEntity.hpp"


namespace sdg {

class ValueToken : public parse::TokenType, public parse::DependentEntity
{
public:
    ValueToken() 
    : TokenType("F", Cardinality::Many)
    , parse::DependentEntity()
    {}
    ~ValueToken() = default;

    virtual void print() const override;
    virtual bool classify(std::string a_token) const override;
    virtual std::pair<std::string, std::string> create_node(std::string a_token) override;
    virtual std::string get_id() const override;
};

}// namespace sdg