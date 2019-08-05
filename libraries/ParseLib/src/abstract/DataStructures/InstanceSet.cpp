// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "InstanceSet.hpp"
#include <iostream>

using namespace std;

InstanceSet::InstanceSet(int32_t hash_table_size)
: hash_table(hash_table_size){}
InstanceSet::~InstanceSet(){}

std::string InstanceSet::get(std::string key)
{
   return hash_table.get(key);
}

int32_t InstanceSet::set(std::string key, std::string value)
{
    hash_table.insert(key, value);
}