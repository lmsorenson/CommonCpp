// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <map>
#include <vector>
#include <memory>
#include "../LexerState.hpp"
#include "../Shape.hpp"

namespace sdg {
    
class DependentEntity : public Shape
{
    char dependent_entity_delimiter_;
    std::string list_delimiter_;
    std::string entity_id_;

    char get_dependent_entity_delimiter() const;
    std::string get_list_delimiter() const;
    std::string get_entity_id() const;

public:
    DependentEntity(Lexer *context, std::string foreign_key);
    ~DependentEntity() = default;

    void generate_link_token() const;

    bool is_complete() const override;
};

}// namespace sdg