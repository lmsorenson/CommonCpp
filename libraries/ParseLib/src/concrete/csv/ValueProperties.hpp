// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once

#include "../../abstract/semantic_analyzer/public/PropertyModel.hpp"

namespace sdg{

class ValueProperties : public PropertySetBase
{
public:
    explicit ValueProperties(const std::string &value, int32_t position, int32_t value_num);
    explicit ValueProperties(const NodeProperties &old);
    explicit ValueProperties(const ValueProperties &properties);

    virtual ~ValueProperties() = default;

    virtual void print() const override;

private:
    const int32_t set_position_;// in other words the record number
};

}// namespace sdg