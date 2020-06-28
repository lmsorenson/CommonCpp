// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/AllowEscapeCharacter.hpp"
#include "../state/ScanningState.hpp"
#include "../state/EscapedState.hpp"
#include <iostream>

using ::sdg::dependent_entity::Scanning;
using ::sdg::dependent_entity::AllowEscapeCharacter;
using ::sdg::dependent_entity::ScanningEscaped;
using ::std::cout;
using ::std::endl;





void AllowEscapeCharacter::initialize(char ch)
{

}

int32_t AllowEscapeCharacter::perform_scan(char ch)
{
    switch (ch)
    {
    case '\"': 
        context_->set_state<ScanningEscaped>('\"');
        break;

    default: 
        context_->set_state<Scanning>(ch);
        break;
    }
    
    return 0;
}

void AllowEscapeCharacter::should_buffer(bool &should_buffer, char ch)
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