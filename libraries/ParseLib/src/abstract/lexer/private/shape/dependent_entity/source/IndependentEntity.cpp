// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/IndependentEntity.hpp"
#include <iostream>

#include "../../../../public/DependentEntity.hpp"
#include "../state/PendingState.hpp"
#include "../../../../Lexer.hpp"

using ::sdg::EndIndependentEntity;
using ::std::cout;
using ::std::endl;
using ::std::pair;


void EndIndependentEntity::initialize(char ch)
{
    context_->set_state<PendingState>();
}

int32_t EndIndependentEntity::perform_scan(char ch)
{
    return 0;
}

void EndIndependentEntity::should_buffer(bool &should_buffer, char ch)
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