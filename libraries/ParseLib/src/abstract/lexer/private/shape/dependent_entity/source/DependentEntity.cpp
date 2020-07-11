// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../../../../public/DependentEntity.hpp"
#include <iostream>

#include "../state/StartIndependentEntity.hpp"
#include "../state/IndependentEntity.hpp"
#include "../state/PendingState.hpp"
#include "../state/ScanningState.hpp"
#include "../state/EscapedState.hpp"
#include "../state/AllowEscapeCharacter.hpp"
#include "../state/DelimiterFoundState.hpp"
#include "../state/FoundState.hpp"
#include "../../../../Lexer.hpp"

using ::sdg::DependentEntity;
using ::sdg::dependent_entity::FoundDependent;
using ::sdg::dependent_entity::Scanning;
using ::sdg::dependent_entity::ScanningEscaped;
using ::sdg::dependent_entity::AllowEscapeCharacter;
using ::sdg::dependent_entity::DelimiterFound;
using ::std::cout;
using ::std::endl;
using ::std::string;
using ::std::pair;

pair<string, string> map_delimiter_pair(const pair<char, char> from) 
{ 
    pair<string, string> to;

    to.first.append(string(1, from.first));
    to.second.append(string(1, from.second));

    return to;
}

inline void DependentEntity::construct_states()
{
    //the first state added is the first scanned.
    this->add_state<StartIndependentEntity>( SetIndependentEntityBegin );
    this->add_state<Scanning>( SetScanningCharacters );
    this->add_state<DelimiterFound>( SetDelimiterFound );
    this->add_state<ScanningEscaped>( SetScanningCharactersEscaped );
    this->add_state<AllowEscapeCharacter>( SetBufferingEscapeCharacters );
    this->add_state<FoundDependent>( SetDependentEntityFound );
    this->add_state<EndIndependentEntity>( SetIndependentEntityFound );
    this->add_state<PendingState>( SetPending );
}

DependentEntity::DependentEntity(
        Lexer *context, 
        string entity_id, 
        Shape::Cardinality cardinality, 
        char entity_delimiter, 
        string shape_delimiter_list, 
        pair<char, char> escape_sequence_delimiters, 
        char escape_char_delimiter) 
: Shape(context, cardinality) 
, entity_id_(entity_id)
, entity_delimiter_(entity_delimiter)
, shape_delimiters_(pair("", shape_delimiter_list))
, escape_sequence_delimiters_(escape_sequence_delimiters)
, escape_char_delimiter_(escape_char_delimiter)
{
    this->construct_states();
}

DependentEntity::DependentEntity(
        Lexer *context, 
        std::string entity_id, 
        Shape::Cardinality cardinality, 
        char entity_delimiter, 
        std::pair<char, char> shape_delimiters, 
        std::pair<char, char> escape_sequence_delimiters,
        char escape_char_delimiter)
: Shape(context, cardinality) 
, entity_id_(entity_id)
, entity_delimiter_(entity_delimiter)
, shape_delimiters_(map_delimiter_pair(shape_delimiters))
, escape_sequence_delimiters_(escape_sequence_delimiters)
, escape_char_delimiter_(escape_char_delimiter)
{
    this->construct_states();
}



int32_t DependentEntity::apply_transition(int32_t enum_value)
{
    switch (enum_value)
    {
    case DependentEntity::StateTransition::SetScanningCharacters:
        this->set_state<Scanning>();
        break;

    case DependentEntity::StateTransition::SetScanningCharactersEscaped:
        this->set_state<ScanningEscaped>();
        break;

    case DependentEntity::StateTransition::SetBufferingEscapeCharacters:
        this->set_state<AllowEscapeCharacter>();
        break;

    case DependentEntity::StateTransition::SetDependentEntityFound:
        this->set_state<FoundDependent>();
        break;
    
    case DependentEntity::StateTransition::SetIndependentEntityBegin:
        this->set_state<StartIndependentEntity>();
        break;

    case DependentEntity::StateTransition::SetIndependentEntityFound:
        this->set_state<EndIndependentEntity>();
        break;

    case DependentEntity::StateTransition::SetPending:
        this->set_state<PendingState>();
        break;

    case DependentEntity::StateTransition::SetDelimiterFound:
        this->set_state<DelimiterFound>();
        break;

    default:
        return 0;
        break;
    }

    return 1;
}

bool DependentEntity::matches_shape_delimiter(char ch) const
{
    for(auto itr = shape_delimiters_.second.begin(); itr != shape_delimiters_.second.end(); ++itr)
    {
        if (*itr == ch)
            return true;
    }

    return false;
}

bool DependentEntity::matches_entity_delimiter(char ch) const
{
    return (ch == entity_delimiter_);
}

bool DependentEntity::matches_escape_sequence_open(char ch) const
{
    return (ch == escape_sequence_delimiters_.first);
}

bool DependentEntity::matches_escape_sequence_close(char ch) const
{
    return (ch == escape_sequence_delimiters_.second);
}

bool DependentEntity::matches_escape_char_delimiter(char ch) const
{
    return (ch == escape_char_delimiter_);
}

void DependentEntity::DependentEntity::generate_link_token() const
{
    generate_token(entity_id_);
}

string DependentEntity::get_entity_id() const
{
    return entity_id_;
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