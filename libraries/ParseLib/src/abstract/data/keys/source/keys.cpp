// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../keys.hpp"


sdg::hash::KeyInstance::KeyInstance(std::string a_value, bool a_is_partial_key)
: value_(a_value)
, is_partial_key_(a_is_partial_key)
{}


bool sdg::hash::KeyInstance::is_partial_key()
{
    return is_partial_key_;
}
std::string sdg::hash::KeyInstance::value()
{
    return value_;
}



sdg::hash::DescriptorInstance::DescriptorInstance()
: id_("")
, value_(-1)
, attribute_scale_(Attribute::Scale::Unknown)
, b_is_found_(false)
{}

sdg::hash::DescriptorInstance::DescriptorInstance(std::string a_descriptor_id, Attribute::Scale a_attr_scale)
: id_(a_descriptor_id)
, value_(-1)
, attribute_scale_(a_attr_scale)
, b_is_found_(false)
{}

int32_t sdg::hash::DescriptorInstance::get_descriptor_value() const
{
    return value_;
}
std::string sdg::hash::DescriptorInstance::get_descriptor_id() const
{
    return id_;
}
sdg::Attribute::Scale sdg::hash::DescriptorInstance::get_scale() const
{
    return attribute_scale_;
}
bool sdg::hash::DescriptorInstance::is_found() const
{
    return b_is_found_;
}

void sdg::hash::DescriptorInstance::set_value(int32_t a_value)
{
    value_ = a_value;
}
void sdg::hash::DescriptorInstance::set_found()
{
    b_is_found_ = true;
}