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

}

int32_t AllowEscapeCharacter::perform_scan(char ch)
{
    switch (ch)
    {
    case '\"': 
        return DependentEntity::StateTransition::SetScanningCharactersEscaped;
        break;

    default: 
        return DependentEntity::StateTransition::SetScanningCharacters;
        break;
    }
}

void AllowEscapeCharacter::should_buffer(bool &should_buffer, char ch)
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