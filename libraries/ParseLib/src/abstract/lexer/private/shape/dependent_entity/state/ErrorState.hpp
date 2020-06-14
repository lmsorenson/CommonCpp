// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../LexerState.hpp"

namespace sdg {

class ErrorState : public LexerState
{
public:
    ErrorState(Lexer *context) : ErrorState(context){}
    virtual ~ErrorState();

    virtual void performScan(char ch) override;
};

}// namespace sdg