// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../private/sequence/SequenceElement.hpp"
#include "../../intermediate/node.hpp"


namespace sdg {
namespace parse {

class TokenType : public SequenceElement
{
    std::string id_;

public:
    explicit TokenType(const std::string &token_id, Cardinality cardinality = Cardinality::One) : SequenceElement(cardinality), id_(token_id) {}
    virtual ~TokenType() = default;

    virtual void print() const override;
    virtual bool classify(const std::string &token) const = 0;
    virtual std::pair<std::string, std::string> create_node(const std::string &a_token) = 0;

    virtual std::shared_ptr<TokenType> evaluate(const std::string &token, MatchStatus &status) override;
    std::string get_typeid() const;
};

}// namespace parser
}// namespace sdg