// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/AllowEscapeCharacter.hpp"
#include "../state/ScanningState.hpp"
#include "../state/EscapedState.hpp"
#include "../../../../public/DependentEntity.hpp"
#include <iostream>

using ::sdg::dependent_entity::Scanning;
using ::sdg::dependent_entity::AllowEscapeCharacter;
using ::sdg::dependent_entity::ScanningEscaped;
using ::std::cout;
using ::std::endl;





void AllowEscapeCharacter::initialize(char ch)
{
    LexerState::initialize(ch);
}

void AllowEscapeCharacter::update()
{
    LexerState::update();
}

int32_t AllowEscapeCharacter::perform_scan(char ch)
{
    int32_t result_transition_code;
    auto ctx = dynamic_cast<DependentEntity*>(context_);
    if (!ctx)
        return -1;

    //delay the transition to give the lexer time to buffer the character.
    result_transition_code = delayed( Delay::NoDelay,
        [=](){
            if( ctx->matches_escape_sequence_close(ch) )
                return DependentEntity::StateTransition::None;
            else
                return DependentEntity::StateTransition::SetScanningCharacters;
        });

    return (result_transition_code != -1) 
    ? result_transition_code
    : DependentEntity::StateTransition::SetScanningCharactersEscaped;
}

void AllowEscapeCharacter::should_buffer(bool &should_buffer, char ch)
{
    switch (ch)
    {
    case '\"':
        should_buffer = true;
        break;

    default: 
        should_buffer = true;
        break;
    }
}