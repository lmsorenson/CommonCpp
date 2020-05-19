// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../../../../public/DependentEntity.hpp"
#include <iostream>

#include "../state/StartIndependentEntity.hpp"
#include "../state/IndependentEntity.hpp"
#include "../state/PendingState.hpp"
#include "../state/ScanningState.hpp"
#include "../state/EscapedState.hpp"
#include "../state/FoundState.hpp"
#include "../../../../Lexer.hpp"

using ::sdg::DependentEntity;
using ::sdg::dependent_entity::FoundDependent;
using ::sdg::dependent_entity::Scanning;
using ::sdg::dependent_entity::ScanningEscaped;
using ::std::cout;
using ::std::endl;
using ::std::string;
using ::std::pair;


DependentEntity::DependentEntity(Lexer *context, std::string entity_id, Shape::Cardinality cardinality, char entity_delimiter, std::string shape_delimiter) 
: Shape(context, cardinality) 
, entity_id_(entity_id)
, entity_delimiter_(entity_delimiter)
, shape_delimiter_(shape_delimiter)
{
    this->add_state<StartIndependentEntity>();
    this->add_state<Scanning>();
    this->add_state<ScanningEscaped>();
    this->add_state<FoundDependent>();
    this->add_state<EndIndependentEntity>();
    this->add_state<PendingState>();
}

void DependentEntity::generate_link_token() const
{
    generate_token(entity_id_);
}

std::string DependentEntity::get_entity_id() const
{
    return entity_id_;
}

char DependentEntity::get_entity_delimiter() const
{
    return entity_delimiter_;
}

std::string DependentEntity::get_shape_delimiter() const
{
    return shape_delimiter_;
}

bool DependentEntity::is_complete() const
{
    string key = typeid(EndIndependentEntity).name();
    auto end_state = states_.at(key);

    switch (cardinality_)
    {
    case Cardinality::One:
        return (end_state->occurances() >= 1);
        break;
    
    default:
    case Cardinality::Many:
        return false;
        break;
    }
}

int32_t DependentEntity::transition() const
{
    return 0;
}