// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <objects/instance.hpp>


using ::std::string;

void sdg::Instance::add_value(std::string str_value)
{
    value_.push_back(str_value);
}

void sdg::Instance::set_key(std::string a_key)
{
    key_ = a_key;
}