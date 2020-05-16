// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../DependentEntity.hpp"
#include <iostream>

#include "../state/IndependentEntity.hpp"
#include "../state/PendingState.hpp"
#include "../state/ScanningState.hpp"
#include "../state/EscapedState.hpp"
#include "../state/FoundState.hpp"
#include "../../../Lexer.hpp"

using ::sdg::dependent_entity::FoundDependent;
using ::sdg::dependent_entity::Scanning;
using ::sdg::dependent_entity::ScanningEscaped;
using ::std::cout;
using ::std::endl;
using ::std::pair;



::sdg::DependentEntity::DependentEntity(Lexer *context) 
: Shape(context) 
{
    this->add_state<IndependentEntity>();
    this->add_state<PendingState>();
    this->add_state<Scanning>();
    this->add_state<ScanningEscaped>();
    this->add_state<FoundDependent>();
}