// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/parser/public/TokenType.hpp"
#include "../../abstract/parser/public/IndependentEntity.hpp"


namespace sdg {
    
class HeaderToken : public parse::TokenType, public parse::IndependentEntity
{
public:
    HeaderToken() : TokenType("H"), parse::IndependentEntity() {}
    virtual ~HeaderToken() = default;

    virtual bool classify(std::string a_token) const override;
    virtual std::pair<std::string, std::string> create_node(std::string a_token) override;
    virtual std::string get_id() const override;
};

}// namespace sdg