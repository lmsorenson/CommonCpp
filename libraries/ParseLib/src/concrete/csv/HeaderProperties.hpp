// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/semantic_analyzer/public/PropertyModel.hpp"

namespace sdg {

class HeaderProperties : public PropertySetBase
{
public:
    explicit HeaderProperties(const std::string &value, int32_t position, int32_t value_num);
    explicit HeaderProperties(const NodeProperties &old);
    explicit HeaderProperties(const HeaderProperties &properties);

    virtual ~HeaderProperties() = default;

    int32_t number_of_values() const;
    virtual void print() const override;

private:
    const int32_t set_position_;// in other words the record number
    const int32_t value_num_;// number of values in the record
};

}// namespace sdg