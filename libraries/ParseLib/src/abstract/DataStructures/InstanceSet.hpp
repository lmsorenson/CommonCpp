// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "Hash.hpp"

using namespace std;



class InstanceSet
{
    hTable hash_table;

public:
    InstanceSet() = default;
    InstanceSet(int32_t hash_table_size);
    ~InstanceSet();

    std::string get(std::string key);
    int32_t set(std::string key, std::string value);
};