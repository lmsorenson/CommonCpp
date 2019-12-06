// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../plInstance.hpp"


using ::std::string;

void plInstance::add(std::string str_value)
{
    value.push_back(str_value);
}

void plInstance::SetKey(std::string a_key)
{
    key = a_key;
}