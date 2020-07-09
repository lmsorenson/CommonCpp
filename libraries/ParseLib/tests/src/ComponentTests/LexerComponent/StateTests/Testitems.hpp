#pragma once
#include "../../../../../src/abstract/lexer/private/shape/LexerState.hpp"
#include "../../../../../src/abstract/lexer/Lexer.hpp"


class MockLexerStateA : public ::sdg::LexerState
{
public:
    MockLexerStateA(::sdg::Shape *context, int32_t state_code) 
    : LexerState(context, state_code)
    {}
    virtual ~MockLexerStateA() = default;

    virtual void initialize(char ch = '\0') override
    {

    }

    virtual int32_t perform_scan(char ch) override
    {

    }
private:
};