// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/PendingState.hpp"
#include "../state/IndependentEntity.hpp"
#include "../state/ScanningState.hpp"
#include "../state/EscapedState.hpp"
#include "../DependentEntity.hpp"

#include "../../../Lexer.hpp"

using ::sdg::PendingState;

void PendingState::initialize(char ch)
{
    
}

void PendingState::perform_scan(char ch)
{
    switch (ch)
    {
    case '\"':
        context_->set_state<dependent_entity::ScanningEscaped>();
        break;

    default: 
        context_->set_state<dependent_entity::Scanning>();
        break;
    }
}

void PendingState::should_buffer(bool &should_buffer, char ch)
{
    switch (ch)
    {
    case '\"':
    case ',':
    case '\r':
    case '\n': 
        should_buffer = false;
        break;

    default: 
        should_buffer = true;
        break;
    }
}