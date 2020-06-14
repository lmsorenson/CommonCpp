// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/EscapedState.hpp"
#include "../state/ScanningState.hpp"
#include "../state/AllowEscapeCharacter.hpp"
#include <iostream>

using ::sdg::dependent_entity::Scanning;
using ::sdg::dependent_entity::ScanningEscaped;
using ::sdg::dependent_entity::AllowEscapeCharacter;
using ::std::cout;
using ::std::endl;





void ScanningEscaped::initialize(char ch)
{

}

void ScanningEscaped::perform_scan(char ch)
{
    if (ch=='\"')
        context_->set_state<AllowEscapeCharacter>('\"');

    else if (ch=='\"') 
        context_->set_state<Scanning>('\"');

    else
        context_->set_state<ScanningEscaped>();
}

void ScanningEscaped::should_buffer(bool &should_buffer, char ch)
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