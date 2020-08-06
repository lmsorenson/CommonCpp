// Copyright 2020, Lucas Sorenson, All rights reserved.s
#include "../RecordProperties.hpp"

using ::sdg::RecordProperties;
using ::std::string;
using ::std::cout;

RecordProperties::RecordProperties(const string &value, int32_t position, int32_t value_num)
: PropertySetBase(value)
, set_position_(position)
, value_num_(value_num)
{}

RecordProperties::RecordProperties(const NodeProperties &old)
: PropertySetBase(old.get_token_value())
, set_position_(-1)
, value_num_(old.number_of_children())
{}

RecordProperties::RecordProperties(const RecordProperties &properties)
: PropertySetBase(properties.value_)
, set_position_(properties.set_position_)
, value_num_(properties.value_num_)
{}

void RecordProperties::print() const
{
    cout << "value: " << value_ << " set position: " << set_position_ << " value num: " << value_num_;
}

int32_t RecordProperties::number_of_values() const
{
    return value_num_;
}