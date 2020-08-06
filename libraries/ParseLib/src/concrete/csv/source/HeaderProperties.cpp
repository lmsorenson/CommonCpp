// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../HeaderProperties.hpp"

using ::sdg::HeaderProperties;
using ::std::string;
using ::std::cout;

HeaderProperties::HeaderProperties(const string &value, int32_t position, int32_t value_num)
: PropertySetBase(value)
, set_position_(position)
, value_num_(value_num)
{}

HeaderProperties::HeaderProperties(const NodeProperties &old)
: PropertySetBase(old.get_token_value())
, set_position_(-1)
, value_num_(old.number_of_children())
{}

HeaderProperties::HeaderProperties(const HeaderProperties &properties)
: PropertySetBase(properties.value_)
, set_position_(properties.set_position_)
, value_num_(properties.value_num_)
{}

int32_t HeaderProperties::number_of_values() const
{
    return value_num_;
}

void HeaderProperties::print() const
{
    cout << "value: " << value_ << " set position value: " << set_position_ << " value num: " << value_num_;
}