// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/EscapedState.hpp"
#include "../state/ScanningState.hpp"
#include "../state/AllowEscapeCharacter.hpp"
#include "../../../../public/DependentEntity.hpp"
#include <iostream>

using ::sdg::dependent_entity::Scanning;
using ::sdg::dependent_entity::ScanningEscaped;
using ::sdg::dependent_entity::AllowEscapeCharacter;
using ::sdg::DependentEntity;
using ::std::cout;
using ::std::endl;





void ScanningEscaped::initialize(char ch)
{

}

int32_t ScanningEscaped::perform_scan(char ch)
{
    auto ctx = dynamic_cast<DependentEntity*>(context_);

    if (ch=='\"'  && num_delimiters>=1)
        return DependentEntity::StateTransition::SetDelimiterFound;

    if (ch=='\"' && num_delimiters>=1) 
        return DependentEntity::StateTransition::SetScanningCharacters;

    else
        return DependentEntity::StateTransition::SetScanningCharactersEscaped;
}

void ScanningEscaped::should_buffer(bool &should_buffer, char ch)
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

void ScanningEscaped::update()
{
    if (num_delimiters > 0)
    {
        num_delimiters--;
    }
    else
    {
        num_delimiters = 0 + 1;
    }
}

void ScanningEscaped::on_transition()
{

    
}