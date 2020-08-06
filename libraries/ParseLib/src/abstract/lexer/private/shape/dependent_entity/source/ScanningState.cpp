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
    auto ctx = dynamic_cast<DependentEntity*>(context_);
    if (!ctx)
        return -1;

    if ( ctx->matches_escape_sequence_open(ch) )
    {
        return DependentEntity::StateTransition::SetScanningCharactersEscaped;
    }
    else if(ctx->matches_shape_delimiter(ch) || ctx->matches_entity_delimiter(ch))
    {
        return DependentEntity::StateTransition::SetDependentEntityFound;
    }
    else
    {
        return DependentEntity::StateTransition::None;
    }
}

void Scanning::should_buffer(bool &should_buffer, char ch)
{
    auto ctx = dynamic_cast<DependentEntity*>(context_);
    if (!ctx)
        return;

    if ( ctx->matches_shape_delimiter(ch) || 
        ctx->matches_entity_delimiter(ch) || 
        ctx->matches_escape_sequence_open(ch) ||
        ctx->matches_escape_sequence_close(ch) )
    {
        should_buffer = false;
    }
    else
    {
        should_buffer = true;
    }
}