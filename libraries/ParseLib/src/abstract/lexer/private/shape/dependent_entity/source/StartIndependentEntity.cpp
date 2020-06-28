// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/StartIndependentEntity.hpp"
#include <iostream>

#include "../../../../public/DependentEntity.hpp"
#include "../state/ScanningState.hpp"
#include "../state/EscapedState.hpp"
#include "../../../../Lexer.hpp"

using ::sdg::StartIndependentEntity;
using ::sdg::DependentEntity;
using ::std::cout;
using ::std::endl;
using ::std::pair;


void StartIndependentEntity::initialize(char ch)
{
    //generates a token that indicates the indepenent entity that dependent entities will be 
    //dependent on.
    if(context_)
        static_cast<DependentEntity * const>(context_)->generate_link_token();
}

int32_t StartIndependentEntity::perform_scan(char ch)
{
    switch (ch)
    {
    case '\r':
    case '\n':
        break;

    case '\"':
        return DependentEntity::StateTransition::SetScanningCharactersEscaped;
        break;

    default: 
        return DependentEntity::StateTransition::SetScanningCharacters;
        break;
    }
    return 0;
}


void StartIndependentEntity::should_buffer(bool &should_buffer, char ch)
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