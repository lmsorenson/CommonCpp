// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/parser/public/TokenType.hpp"
#include "../../abstract/parser/public/IndependentEntity.hpp"


namespace sdg {

class RecordToken : public parse::TokenType, public parse::IndependentEntity
{
public:
    RecordToken() : TokenType("R"), parse::IndependentEntity() {}
    virtual ~RecordToken() = default;

    virtual bool classify(const std::string &a_token) const override;
    virtual std::pair<std::string, std::string> create_node(const std::string &token) override;
    virtual std::string get_id() const override;
};

}// namespace sdg