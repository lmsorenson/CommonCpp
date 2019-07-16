// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "Hash.hpp"

using namespace std;



class AbstractDataStructure
{
    hTable hash_table;

public:
    AbstractDataStructure(int32_t hash_table_size);
    ~AbstractDataStructure();

    std::string get(std::string key);
    int32_t set(std::string key, std::string value);
};