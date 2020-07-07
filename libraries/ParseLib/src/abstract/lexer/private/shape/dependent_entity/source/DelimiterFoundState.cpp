// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/DelimiterFoundState.hpp"
#include "../state/AllowEscapeCharacter.hpp"
#include "../state/ScanningState.hpp"
#include "../state/EscapedState.hpp"
#include "../../../../public/DependentEntity.hpp"
#include <iostream>

using ::sdg::dependent_entity::AllowEscapeCharacter;
using ::sdg::dependent_entity::DelimiterFound;
using ::sdg::dependent_entity::ScanningEscaped;
using ::std::cout;
using ::std::endl;





void DelimiterFound::initialize(char ch)
{
    char_count_=0;
}

void DelimiterFound::update()
{
    char_count_++;
}

int32_t DelimiterFound::perform_scan(char ch)
{
    DependentEntity::StateTransition result_transition;

    if ( char_count_ > 0 )
    {
        if(ch == '\"')
            result_transition = DependentEntity::StateTransition::SetBufferingEscapeCharacters;
        else
            result_transition = DependentEntity::StateTransition::SetScanningCharacters;
    }
    else
    {
        result_transition = DependentEntity::StateTransition::None;
    }

    return result_transition;
}

void DelimiterFound::should_buffer(bool &should_buffer, char ch)
{
    switch (ch)
    {
    case '\"':
        should_buffer = false;
        break;

    default: 
        should_buffer = true;
        break;
    }
}