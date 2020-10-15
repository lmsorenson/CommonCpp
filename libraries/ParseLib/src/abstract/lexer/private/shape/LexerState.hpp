// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <stdint.h>
#include <vector>
#include <functional>

namespace sdg {

class Shape;

class LexerState
{
public:
    LexerState(Shape *context, int32_t state_code) 
    : context_(context),
    occurances_(0),
    char_num_(0),
    code_(state_code)
    {}
    virtual ~LexerState() = default;

    virtual void initialize(char ch = '\0');
    virtual void reset();
    virtual void on_transition();
    virtual void update();

    virtual int32_t perform_scan(char ch) = 0;
    virtual void should_buffer(bool &should_buffer, char ch);
    
    int32_t to_state_code() const;
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

    enum Delay : int32_t
    {
        NoDelay = 0,
        OneCharacter
    };

protected:
    Shape * const context_;
    int32_t delayed(Delay delay, std::function<int32_t()> delayed_function);

private:
    
    int32_t occurances_;        //occurances refer to the number of times this state_ is used.
    int32_t char_num_;          //char_num_ refers to the number of characters scanned in the current session of this state_.
    int32_t code_;
};

}// namespace sdg