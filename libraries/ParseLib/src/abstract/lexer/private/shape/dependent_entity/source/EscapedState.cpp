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
    if (!ctx)
        return -1;

    if (ctx->matches_escape_char_delimiter(ch)  && num_delimiters>=1)
        return DependentEntity::StateTransition::SetDelimiterFound;

    if (ctx->matches_escape_sequence_close(ch) && num_delimiters>=1) 
        return DependentEntity::StateTransition::SetScanningCharacters;

    else
        return DependentEntity::StateTransition::SetScanningCharactersEscaped;
}

void ScanningEscaped::should_buffer(bool &should_buffer, char ch)
{
    auto ctx = dynamic_cast<DependentEntity*>(context_);
    if (!ctx)
        return;

    if ( ctx->matches_escape_sequence_open(ch) || ctx->matches_escape_sequence_close(ch) )
    {
        should_buffer = false;
    }
    else
    {
        should_buffer = true;
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