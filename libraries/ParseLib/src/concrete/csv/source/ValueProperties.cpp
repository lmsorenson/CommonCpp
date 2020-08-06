// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../ValueProperties.hpp"

using ::sdg::ValueProperties;
using ::std::string;
using ::std::cout;

ValueProperties::ValueProperties(const string &value, int32_t position, int32_t value_num)
: PropertySetBase(value)
, set_position_(position)
{}

ValueProperties::ValueProperties(const NodeProperties &old)
: PropertySetBase(old.get_token_value())
, set_position_(-1)
{}

ValueProperties::ValueProperties(const ValueProperties &properties)
: PropertySetBase(properties.value_)
, set_position_(properties.set_position_)
{}

void ValueProperties::print() const
{
    cout << "value: " << value_ << " set position value: " << set_position_;
}