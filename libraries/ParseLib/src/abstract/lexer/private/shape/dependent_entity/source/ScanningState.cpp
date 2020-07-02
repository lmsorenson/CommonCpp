// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/ScanningState.hpp"
#include <iostream>

#include "../../../../public/DependentEntity.hpp"
#include "../state/FoundState.hpp"
#include "../state/EscapedState.hpp"
#include "../../../../Lexer.hpp"

using ::sdg::dependent_entity::Scanning;
using ::sdg::dependent_entity::FoundDependent;
using ::sdg::dependent_entity::ScanningEscaped;
using ::sdg::DependentEntity;
using ::std::cout;
using ::std::endl;
using ::std::pair;




void Scanning::initialize(char ch)
{
    if (ch == '\0')
        return;
}

int32_t Scanning::perform_scan(char ch)
{
    switch (ch)
    {
    case '\"':
        return DependentEntity::StateTransition::SetScanningCharactersEscaped;
        break;

    case ',':
    case '\r':
    case '\n': 
        return DependentEntity::StateTransition::SetDependentEntityFound;
        break;

    default: 
        return DependentEntity::StateTransition::None;
        break;
    }
}

void Scanning::should_buffer(bool &should_buffer, char ch)
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