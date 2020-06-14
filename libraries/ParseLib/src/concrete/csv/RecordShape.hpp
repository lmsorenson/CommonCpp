// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/lexer/public/DependentEntity.hpp"


namespace sdg {

class RecordShape : public DependentEntity
{
public:
    RecordShape(Lexer *context, std::string entity_id, Shape::Cardinality cardinality)
    : DependentEntity(context, entity_id, cardinality, ',', "\r\n")
    {}
    virtual ~RecordShape() = default;

    virtual int32_t transition() const;
};

}// namespace sdg