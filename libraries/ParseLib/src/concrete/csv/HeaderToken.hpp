// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/parser/public/TokenType.hpp"
#include "../../abstract/parser/public/IndependentEntity.hpp"


namespace sdg {
    
class HeaderToken : public parse::TokenType, public parse::IndependentEntity
{
public:
    HeaderToken();
    virtual ~HeaderToken() = default;

    //override classify() a header token
    virtual bool classify(const std::string &a_token) const override;

    //override create_node() a header token
    virtual std::pair<std::string, std::string> create_node(const std::string &a_token) override;

    //override get_id() a header token
    virtual std::string get_id() const override;
};

}// namespace sdg