// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "Hash.hpp"
#include "plInstance.hpp"


using namespace std;

class plDataSet
{
    enum State : int32_t
    {
        DATA_SET_GOOD,
        DATA_SET_BAD,
        DATA_SET_EMPTY,
        UNKNOWN
    } state;

    //a hash table to store the data in.
    hTable hash_table;

public:
    plDataSet();
    plDataSet(State s);
    plDataSet(int32_t hash_table_size);
    ~plDataSet();

    plInstance get(std::string aKey);
    int32_t set(std::string aKey, hValue aValue);
};