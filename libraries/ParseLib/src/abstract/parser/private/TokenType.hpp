// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "sequence/SequenceElement.hpp"


namespace sdg {
namespace parse {

class TokenType : public SequenceElement
{
public:
    TokenType() : SequenceElement() {}
    ~TokenType() = default;

};

}// namespace parser
}// namespace sdg