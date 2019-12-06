// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../instance.hpp"


using ::std::string;

void sdg::Instance::add(std::string str_value)
{
    value.push_back(str_value);
}

void sdg::Instance::SetKey(std::string a_key)
{
    key = a_key;
}