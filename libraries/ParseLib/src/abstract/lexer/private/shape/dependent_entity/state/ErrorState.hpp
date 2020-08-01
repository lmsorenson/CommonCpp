// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../LexerState.hpp"

namespace sdg {

class ErrorState : public LexerState
{
public:
    explicit ErrorState(Lexer *context) : ErrorState(context){}
    virtual ~ErrorState();

    virtual int32_t performScan(char ch) override;
};

}// namespace sdg