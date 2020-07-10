// Copyright 2020 Lucas Sorenson, All rights reserved.
#include "../LexerState.hpp"


using ::sdg::LexerState;


int32_t LexerState::delayed(Delay delay, std::function<int32_t()> delayed_function)
{
    if (char_num_ == (int32_t)delay)
    {
        return delayed_function();
    }
    else
    {
        return -1;
    }
}

void LexerState::initialize(char ch)
{
    //reset this count when a new session begins.
    char_num_ = 0;
}

void LexerState::reset()
{
}

void LexerState::should_buffer(bool &should_buffer, char ch)
{
    should_buffer = true;
}

int32_t LexerState::to_state_code() const
{
    return code_;
}

int32_t LexerState::occurances() const
{
    return occurances_;
}

void LexerState::update()
{
    char_num_++;
}

void LexerState::on_transition()
{

}