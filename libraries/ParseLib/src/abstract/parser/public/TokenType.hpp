// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../private/sequence/SequenceElement.hpp"


namespace sdg {
namespace parse {

class TokenType : public SequenceElement
{
public:
    explicit TokenType(Cardinality cardinality = Cardinality::One) : SequenceElement(cardinality) {}
    ~TokenType() = default;

    virtual void print() const override;
    virtual bool classify(std::string token) const = 0;
    virtual bool evaluate(std::string token, std::function<void()> next_element, std::function<void(int32_t type, std::string message)> handle_error) override;
};

}// namespace parser
}// namespace sdg