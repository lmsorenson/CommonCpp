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