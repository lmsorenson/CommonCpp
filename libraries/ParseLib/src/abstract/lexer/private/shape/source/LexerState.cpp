// Copyright 2020 Lucas Sorenson, All rights reserved.
#include "../LexerState.hpp"


using ::sdg::LexerState;




void LexerState::initialize(char ch)
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

}

void LexerState::on_transition()
{

}