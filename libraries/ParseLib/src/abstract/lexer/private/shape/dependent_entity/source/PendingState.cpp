// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/PendingState.hpp"
#include "../state/StartIndependentEntity.hpp"
#include "../../../../public/DependentEntity.hpp"

#include "../../../../Lexer.hpp"

using ::sdg::PendingState;

void PendingState::initialize(char ch)
{
    
}

int32_t PendingState::perform_scan(char ch)
{
    auto ctx = dynamic_cast<DependentEntity*>(context_);
    if (!ctx)
        return -1;

    if ( ctx->matches_shape_delimiter(ch) )
    {
        return DependentEntity::StateTransition::None;
    }
    else
    {
        return DependentEntity::StateTransition::SetIndependentEntityBegin;
    }
}

void PendingState::should_buffer(bool &should_buffer, char ch)
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