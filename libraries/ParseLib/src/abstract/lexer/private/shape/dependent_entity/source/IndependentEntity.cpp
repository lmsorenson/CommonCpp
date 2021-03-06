// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/IndependentEntity.hpp"
#include <iostream>

#include "../../../../public/DependentEntity.hpp"
#include "../state/PendingState.hpp"
#include "../../../../Lexer.hpp"

using ::sdg::EndIndependentEntity;
using ::std::cout;
using ::std::endl;
using ::std::pair;


void EndIndependentEntity::initialize(char ch)
{
    context_->set_state<PendingState>();
}

int32_t EndIndependentEntity::perform_scan(char ch)
{
    return DependentEntity::StateTransition::None;
}

void EndIndependentEntity::should_buffer(bool &should_buffer, char ch)
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