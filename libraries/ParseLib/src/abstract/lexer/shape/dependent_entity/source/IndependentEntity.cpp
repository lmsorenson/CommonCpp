// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/IndependentEntity.hpp"
#include <iostream>

#include "../DependentEntity.hpp"
#include "../state/PendingState.hpp"
#include "../../../Lexer.hpp"

using ::sdg::IndependentEntity;
using ::std::cout;
using ::std::endl;
using ::std::pair;


void IndependentEntity::initialize(char ch)
{
    cout << "NEW RECORD ";
    context_->generate_token("R");

    context_->set_state<PendingState>();
}

void IndependentEntity::perform_scan(char ch)
{
}


void IndependentEntity::should_buffer(bool &should_buffer, char ch)
{
    switch (ch)
    {
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