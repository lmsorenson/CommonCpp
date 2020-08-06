// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/parser/public/TokenType.hpp"
#include "../../abstract/parser/public/DependentEntity.hpp"


namespace sdg {

class ValueToken : public parse::TokenType, public parse::DependentEntity
{
public:
    ValueToken();
    virtual ~ValueToken() = default;

    //override classify() for ValueTokens
    virtual bool classify(const std::string &a_token) const override;

    //override create_node() for ValueTokens
    virtual std::pair<std::string, std::string> create_node(const std::string &a_token) override;

    //override get_id() for ValueTokens
    virtual std::string get_id() const override;
};

}// namespace sdg