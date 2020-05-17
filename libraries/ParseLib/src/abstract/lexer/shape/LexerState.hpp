// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>

namespace sdg {

class Shape;

class LexerState
{
    int32_t occurances_;

protected:
    Shape * const context_;

public:
    LexerState(Shape *context) : context_(context) {}
    virtual ~LexerState() = default;

    virtual void initialize(char ch = '\0');
    virtual void perform_scan(char ch) = 0;
    virtual void should_buffer(bool &should_buffer, char ch);

    int32_t occurances() const;

    LexerState& operator++()
    {
        occurances_++;
        return *this;
    }

    LexerState& operator++(int)
    {
        occurances_++;
        return *this;
    }
};

}// namespace sdg