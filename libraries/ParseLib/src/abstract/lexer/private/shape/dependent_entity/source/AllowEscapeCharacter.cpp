// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/AllowEscapeCharacter.hpp"
#include "../state/ScanningState.hpp"
#include "../state/EscapedState.hpp"
#include "../../../../public/DependentEntity.hpp"
#include <iostream>

using ::sdg::dependent_entity::Scanning;
using ::sdg::dependent_entity::AllowEscapeCharacter;
using ::sdg::dependent_entity::ScanningEscaped;
using ::std::cout;
using ::std::endl;





void AllowEscapeCharacter::initialize(char ch)
{
    char_count_ = 0;
}

int32_t AllowEscapeCharacter::perform_scan(char ch)
{
    DependentEntity::StateTransition result_transition;
    auto ctx = dynamic_cast<DependentEntity*>(context_);

    if (char_count_ < 1)
    {
        if (ch == '\"')
            result_transition = DependentEntity::StateTransition::None;

        else
            result_transition = DependentEntity::StateTransition::SetScanningCharacters;
    }
    else
    {
        result_transition = DependentEntity::StateTransition::SetScanningCharactersEscaped;
    }

    return result_transition;
}

void AllowEscapeCharacter::update()
{
    char_count_++;
}

void AllowEscapeCharacter::should_buffer(bool &should_buffer, char ch)
{
    switch (ch)
    {
    case '\"':
        should_buffer = true;
        break;

    default: 
        should_buffer = true;
        break;
    }
}