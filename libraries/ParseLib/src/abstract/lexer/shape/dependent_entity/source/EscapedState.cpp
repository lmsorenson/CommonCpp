// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../state/EscapedState.hpp"
#include "../state/ScanningState.hpp"
#include <iostream>

using ::sdg::dependent_entity::Scanning;
using ::sdg::dependent_entity::ScanningEscaped;
using ::std::cout;
using ::std::endl;





void ScanningEscaped::initialize(char ch)
{

}

void ScanningEscaped::perform_scan(char ch)
{
    switch (ch)
    {
    case '\"': 
        context_->set_state<Scanning>('\"');
        break;

    default: 
        context_->set_state<ScanningEscaped>();
        break;
    }
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