// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "Hash.hpp"

using namespace std;



class AbstractDataStructure
{

public:
    hTable hash_table;

    AbstractDataStructure(int32_t hash_table_size);
    ~AbstractDataStructure();
};