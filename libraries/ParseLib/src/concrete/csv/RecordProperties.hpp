// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/semantic_analyzer/public/PropertyModel.hpp"

namespace sdg {

class RecordProperties : public PropertySetBase
{
public:
    explicit RecordProperties(const std::string &value, int32_t position, int32_t value_num);
    explicit RecordProperties(const NodeProperties &old);
    explicit RecordProperties(const RecordProperties &properties);

    virtual ~RecordProperties() = default;

    virtual void print() const override;
    int32_t number_of_values() const;

private:
    const int32_t set_position_;// in other words the record number
    const int32_t value_num_;// number of values in the record
};

}// namespace sdg