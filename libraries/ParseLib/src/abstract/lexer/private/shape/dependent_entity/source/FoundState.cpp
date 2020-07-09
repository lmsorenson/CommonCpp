// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/FoundState.hpp"
#include <iostream>

#include "../state/IndependentEntity.hpp"
#include "../state/ScanningState.hpp"
#include "../state/EscapedState.hpp"
#include "../../../../Lexer.hpp"
#include "../../../../public/DependentEntity.hpp"

using ::sdg::dependent_entity::FoundDependent;
using ::sdg::dependent_entity::Scanning;
using ::sdg::dependent_entity::ScanningEscaped;
using ::sdg::EndIndependentEntity;
using ::std::cout;
using ::std::endl;
using ::std::pair;
using ::std::string;





void FoundDependent::initialize(char ch)
{
    context_->generate_token( pair<string, string>("F(",")") );

    // if (ch == '\n' || ch == '\r')
    // {
    //     context_->set_state<EndIndependentEntity>();
    // }
}

int32_t FoundDependent::perform_scan(char ch)
{
    auto ctx = dynamic_cast<DependentEntity*>(context_);
    if (!ctx)
        return -1;

    if ( ctx->matches_shape_delimiter(ch) )
    {
        return DependentEntity::StateTransition::SetIndependentEntityFound;
        context_->handle_error({FILE_FORMAT_INVALID});
    }
    else
    {
        return DependentEntity::StateTransition::SetScanningCharacters;
    }
}


void FoundDependent::should_buffer(bool &should_buffer, char ch)
{
    auto ctx = dynamic_cast<DependentEntity*>(context_);
    if (!ctx)
        return;

    if ( ctx->matches_shape_delimiter(ch) || 
        ctx->matches_entity_delimiter(ch) || 
        ctx->matches_escape_sequence_open(ch) ||
        ctx->matches_escape_sequence_close(ch))
    {
        should_buffer = false;
    }
    else
    {
        should_buffer = true;
    }
}