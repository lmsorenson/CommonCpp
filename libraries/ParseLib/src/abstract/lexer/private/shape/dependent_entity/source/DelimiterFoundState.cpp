// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/DelimiterFoundState.hpp"
#include "../state/AllowEscapeCharacter.hpp"
#include "../state/ScanningState.hpp"
#include "../state/EscapedState.hpp"
#include "../../../../public/DependentEntity.hpp"
#include <iostream>

using ::sdg::dependent_entity::AllowEscapeCharacter;
using ::sdg::dependent_entity::DelimiterFound;
using ::sdg::dependent_entity::ScanningEscaped;
using ::std::cout;
using ::std::endl;





void DelimiterFound::initialize(char ch)
{
    LexerState::initialize(ch);
}

void DelimiterFound::update()
{
    LexerState::update();
}

int32_t DelimiterFound::perform_scan(char ch)
{
    int32_t result_transition_code;
    auto ctx = dynamic_cast<DependentEntity*>(context_);
    if (!ctx)
        return -1;

    //delay the transition because the transition depends on the following character.
    result_transition_code = delayed( Delay::OneCharacter,
        [=](){
            if( ctx->matches_escape_sequence_close(ch) )
                return DependentEntity::StateTransition::SetBufferingEscapeCharacters;
            else
                return DependentEntity::StateTransition::SetScanningCharacters;
        });

    return (result_transition_code != -1) 
    ? result_transition_code
    : DependentEntity::StateTransition::None;
}

void DelimiterFound::should_buffer(bool &should_buffer, char ch)
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