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
    cout << "END RECORD ";
    // static_cast<DependentEntity * const>(context_)->generate_link_token();

    context_->set_state<PendingState>();
}

void EndIndependentEntity::perform_scan(char ch)
{
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