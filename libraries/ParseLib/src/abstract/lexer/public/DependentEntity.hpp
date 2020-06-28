// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <map>
#include <vector>
#include <memory>
#include "../private/shape/Shape.hpp"

namespace sdg {
    
class DependentEntity : public Shape
{
public:
    enum StateTransition : int32_t {
        None = 0,
        SetIndependentEntityBegin,
        SetScanningCharacters,
        SetScanningCharactersEscaped,
        SetBufferingEscapeCharacters,
        SetDependentEntityFound,
        SetIndependentEntityFound,
        SetPending
    };

    DependentEntity(Lexer *context, std::string entity_id, Shape::Cardinality cardinality, char entity_delimiter, std::string shape_delimiter);
    virtual ~DependentEntity() = default;

    void generate_link_token() const;

    bool is_complete() const override;
    virtual int32_t transition() const override;

private:
    std::string entity_id_;
    char entity_delimiter_;
    std::string shape_delimiter_;

    char get_entity_delimiter() const;
    std::string get_shape_delimiter() const;
    std::string get_entity_id() const;

    virtual void apply_transition(int32_t enum_value) override;
};



}// namespace sdg