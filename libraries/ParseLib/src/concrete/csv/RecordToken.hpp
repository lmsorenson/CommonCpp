// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/parser/public/TokenType.hpp"


namespace sdg {

class RecordToken : public parse::TokenType
{
public:
    RecordToken() : TokenType() {}
    ~RecordToken() = default;

    virtual void print() const override;
    virtual bool classify(std::string token) const override;
};

}// namespace sdg