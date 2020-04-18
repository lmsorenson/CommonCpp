// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <objects/instance.hpp>

#include <iostream>
#include <string>
#include <vector>

#include <objects/data_set.hpp>



using std::string;
using std::to_string;
using std::vector;

sdg::Instance::Instance(const sdg::DataSet * owner, State a_state)
: kOwner_(owner)
, state_(a_state)
{}

sdg::Instance::Instance(const sdg::DataSet * owner, State a_state, hash::KeyInstance a_key)
: kOwner_(owner)
, state_(a_state)
, key_(a_key)
{}

sdg::Instance::~Instance()
{}

sdg::Instance sdg::Instance::operator[](std::string i)
{
    std::string new_key_buffer;
    new_key_buffer.append(this->key_.as_string()).append("-").append(i);

    return kOwner_->get(new_key_buffer);
}