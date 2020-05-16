// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../LexerState.hpp"

namespace sdg {

class IndependentEntity : public LexerState
{
public:
    IndependentEntity(Shape *context) : LexerState(context){}

    virtual void initialize(char ch) override;
    virtual void perform_scan(char ch) override;
    virtual void should_buffer(bool &should_buffer, char ch) override;
};

}// namespace sdg