// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../LexerState.hpp"

namespace sdg {

class PendingState : public LexerState
{
public:
    PendingState(Shape *context, int32_t state_code) : LexerState(context, state_code){}
    virtual ~PendingState() = default;

    virtual void initialize(char ch) override;
    virtual int32_t perform_scan(char ch) override;
    virtual void should_buffer(bool &should_buffer, char ch) override;
};

}// namespace sdg