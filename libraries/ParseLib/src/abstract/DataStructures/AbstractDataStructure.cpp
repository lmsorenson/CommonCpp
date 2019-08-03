// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "AbstractDataStructure.hpp"
#include <iostream>

using namespace std;

AbstractDataStructure::AbstractDataStructure(int32_t hash_table_size)
: hash_table(hash_table_size){}
AbstractDataStructure::~AbstractDataStructure(){}

std::string AbstractDataStructure::get(std::string key)
{
   return hash_table.get(key);
}

int32_t AbstractDataStructure::set(std::string key, std::string value)
{
    hash_table.insert(key, value);
}