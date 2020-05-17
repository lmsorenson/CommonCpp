// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/StartIndependentEntity.hpp"
#include <iostream>

#include "../DependentEntity.hpp"
#include "../state/ScanningState.hpp"
#include "../state/EscapedState.hpp"
#include "../../../Lexer.hpp"

using ::sdg::StartIndependentEntity;
using ::std::cout;
using ::std::endl;
using ::std::pair;


void StartIndependentEntity::initialize(char ch)
{
    cout << "NEW RECORD ";
    static_cast<DependentEntity * const>(context_)->generate_link_token();
}

void StartIndependentEntity::perform_scan(char ch)
{
    switch (ch)
    {
    case '\r':
    case '\n':
        break;

    case '\"':
        context_->set_state<dependent_entity::ScanningEscaped>();
        break;

    default: 
        context_->set_state<dependent_entity::Scanning>();
        break;
    }
    
}


void StartIndependentEntity::should_buffer(bool &should_buffer, char ch)
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