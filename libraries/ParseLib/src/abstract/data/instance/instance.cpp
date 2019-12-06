// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../instance.hpp"
#include <data_set.hpp>

#include <iostream>
#include <string>
#include <vector>



using std::string;
using std::to_string;
using std::vector;

sdg::Instance::Instance(const sdg::DataSet * owner, State s)
: kOwner_(owner)
, state_(s)
{}

sdg::Instance::~Instance()
{}

sdg::Instance sdg::Instance::operator[](std::string i)
{
    std::string new_key_buffer = this->key_;
    new_key_buffer.append("-").append(i);

    return kOwner_->get(new_key_buffer);
}