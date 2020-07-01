#pragma once
#include "../../../../../src/abstract/lexer/private/shape/Shape.hpp"
#include <gmock/gmock.h>


enum StateTransition : int32_t
{
    None = 0,
    SetStateA,
    SetStateB,
    SetStateC
};

class MockStateA : public ::sdg::LexerState
{
public:
    MockStateA(sdg::Shape *context, int32_t state_code) : LexerState(context, state_code){}
    virtual ~MockStateA() = default;

    MOCK_METHOD(void, initialize, (char ch), (override));
    MOCK_METHOD(int32_t, perform_scan, (char ch), (override));
    MOCK_METHOD(void, should_buffer, (bool &should_buffer, char ch), (override));
};

class MockStateB : public ::sdg::LexerState
{
public:
    MockStateB(sdg::Shape *context, int32_t state_code) : LexerState(context, state_code){}
    virtual ~MockStateB() = default;

    MOCK_METHOD(void, initialize, (char ch), (override));
    MOCK_METHOD(int32_t, perform_scan, (char ch), (override));
    MOCK_METHOD(void, should_buffer, (bool &should_buffer, char ch), (override));
};

class MockStateC : public sdg::LexerState
{
public:
    MockStateC(sdg::Shape *context, int32_t state_code) : LexerState(context, state_code){}
    virtual ~MockStateC() = default;

    MOCK_METHOD(void, initialize, (char ch), (override));
    MOCK_METHOD(int32_t, perform_scan, (char ch), (override));
    MOCK_METHOD(void, should_buffer, (bool &should_buffer, char ch), (override));
};