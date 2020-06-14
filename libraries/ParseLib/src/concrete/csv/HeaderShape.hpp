// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/lexer/public/DependentEntity.hpp"


namespace sdg {

class HeaderShape : public DependentEntity
{
public:
    HeaderShape(Lexer *context, std::string entity_id, Shape::Cardinality cardinality)
    : DependentEntity(context, entity_id, cardinality, ',', "\r\n")
    {}
    virtual ~HeaderShape() = default;

    virtual int32_t transition() const;
};

}// namespace sdg