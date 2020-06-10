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
public:
    explicit TokenType(Cardinality cardinality = Cardinality::One) : SequenceElement(cardinality) {}
    ~TokenType() = default;

    virtual void print() const override;
    virtual bool classify(std::string token) const = 0;
    virtual SyntaxNode create_node(std::string a_token) = 0;

    virtual std::shared_ptr<TokenType> evaluate(std::string token, std::function<void()> next_element, MatchStatus &status) override;
};

}// namespace parser
}// namespace sdg