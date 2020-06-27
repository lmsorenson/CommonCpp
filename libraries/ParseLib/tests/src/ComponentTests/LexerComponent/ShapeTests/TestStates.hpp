#pragma once
#include "../../../../../src/abstract/lexer/private/shape/Shape.hpp"
#include <gmock/gmock.h>

class StateA : public ::sdg::LexerState
{
public:
    StateA(::sdg::Shape *context) : LexerState(context){}
    virtual ~StateA() = default;

    virtual void initialize(char ch) override
    {

    }

    virtual void perform_scan(char ch) override
    {

    }

    virtual void should_buffer(bool &should_buffer, char ch) override
    {

    }
};

class MockStateA : public ::sdg::LexerState
{
public:
    MockStateA(sdg::Shape *context) : LexerState(context){}
    virtual ~MockStateA() = default;

    MOCK_METHOD(void, initialize, (char ch), (override));
    MOCK_METHOD(void, perform_scan, (char ch), (override));
    MOCK_METHOD(void, should_buffer, (bool &should_buffer, char ch), (override));
};



class StateB : public ::sdg::LexerState
{
public:
    StateB(::sdg::Shape *context) : LexerState(context){}
    virtual ~StateB() = default;

    virtual void initialize(char ch) override
    {

    }

    virtual void perform_scan(char ch) override
    {

    }

    virtual void should_buffer(bool &should_buffer, char ch) override
    {

    }
};





class StateC : public ::sdg::LexerState
{
public:
    StateC(::sdg::Shape *context) : LexerState(context){}
    virtual ~StateC() = default;

    virtual void initialize(char ch) override
    {

    }

    virtual void perform_scan(char ch) override
    {

    }

    virtual void should_buffer(bool &should_buffer, char ch) override
    {

    }
};

