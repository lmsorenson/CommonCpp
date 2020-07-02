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
    switch (ch)
    {   
    case '\r':
    case '\n': 
        return DependentEntity::StateTransition::SetIndependentEntityFound;
        context_->handle_error({FILE_FORMAT_INVALID});
        break;

    default: 
        return DependentEntity::StateTransition::SetScanningCharacters;
        break;
    }
}


void FoundDependent::should_buffer(bool &should_buffer, char ch)
{
    switch (ch)
    {
    case '\"':
    case ',':
    case '\r':
    case '\n': 
        should_buffer = false;
        break;

    default: 
        should_buffer = true;
        break;
    }
}