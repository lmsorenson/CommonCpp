// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../LexerState.hpp"

namespace sdg {

class StartIndependentEntity : public LexerState
{
public:
    StartIndependentEntity(Shape *context, int32_t state_code) : LexerState(context, state_code){}
    virtual ~StartIndependentEntity() = default;

    virtual void initialize(char ch) override;
    virtual int32_t perform_scan(char ch) override;
    virtual void should_buffer(bool &should_buffer, char ch) override;
};

}// namespace sdg