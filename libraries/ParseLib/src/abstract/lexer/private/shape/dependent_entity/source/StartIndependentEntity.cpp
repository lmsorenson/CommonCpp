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
    auto ctx = dynamic_cast<DependentEntity*>(context_);
    if (!ctx)
        return -1;

    if ( ctx->matches_shape_delimiter(ch) )
    {
        
    }
    else if( ctx->matches_escape_sequence_open(ch) )
    {
        return DependentEntity::StateTransition::SetScanningCharactersEscaped;
    }
    else
    {
        return DependentEntity::StateTransition::SetScanningCharacters;
    }
}


void StartIndependentEntity::should_buffer(bool &should_buffer, char ch)
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