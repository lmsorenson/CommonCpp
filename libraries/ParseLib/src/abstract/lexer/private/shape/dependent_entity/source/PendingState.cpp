// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/PendingState.hpp"
#include "../state/StartIndependentEntity.hpp"
#include "../../../../public/DependentEntity.hpp"

#include "../../../../Lexer.hpp"

using ::sdg::PendingState;

void PendingState::initialize(char ch)
{
    
}

int32_t PendingState::perform_scan(char ch)
{
    switch (ch)
    {   
    case '\r':
    case '\n': 
        return DependentEntity::StateTransition::None;
        break;

    default: 
        return DependentEntity::StateTransition::SetIndependentEntityBegin;
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