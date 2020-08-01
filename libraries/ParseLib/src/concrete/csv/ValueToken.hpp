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
    virtual ~ValueToken() = default;
    
    virtual bool classify(const std::string &a_token) const override;
    virtual std::pair<std::string, std::string> create_node(const std::string &a_token) override;
    virtual std::string get_id() const override;
};

}// namespace sdg