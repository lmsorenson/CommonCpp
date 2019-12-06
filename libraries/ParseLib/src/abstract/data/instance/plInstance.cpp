// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../plInstance.hpp"
#include <plDataSet.hpp>
#include <iostream>
#include <string>
#include <vector>



using std::string;
using std::to_string;
using std::vector;

plInstance::plInstance(const sdg::plDataSet * owner, State s)
: owning_data_set(owner)
, state(s)
{}

plInstance::~plInstance()
{}

plInstance plInstance::operator[](std::string i)
{
    std::string new_key_buffer = this->key;
    new_key_buffer.append("-").append(i);

    return owning_data_set->get(new_key_buffer);
}