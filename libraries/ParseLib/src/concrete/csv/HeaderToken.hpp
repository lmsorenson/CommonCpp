// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/parser/public/TokenType.hpp"


namespace sdg {
    
class HeaderToken : public parse::TokenType
{
public:
    HeaderToken() : TokenType() {}
    ~HeaderToken() = default;

    virtual void print() const override;
    virtual bool classify(std::string token) const override;
};

}// namespace sdg