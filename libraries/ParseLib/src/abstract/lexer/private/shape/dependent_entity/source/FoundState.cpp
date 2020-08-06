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




//called every time the state is set.
void FoundDependent::initialize(char ch)
{
    LexerState::initialize();
    token_size_ = context_->generate_token( pair<string, string>("F(",")") );
}

//called after the character has been fully processed.
void FoundDependent::update()
{
    LexerState::update();
    token_size_ = -1;
}

int32_t FoundDependent::perform_scan(char ch)
{
    auto ctx = dynamic_cast<DependentEntity*>(context_);
    if (!ctx)
        return -1;

    if( ctx->matches_shape_delimiter(ch) && token_size_ <= 0 )
    {
        context_->handle_error(Error(FILE_FORMAT_INVALID));
        return DependentEntity::StateTransition::None;
    }
    else if ( ctx->matches_shape_delimiter(ch) )
    {
        return DependentEntity::StateTransition::SetIndependentEntityFound;
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