// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "plInstance.hpp"
#include "Hash.hpp"

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

    hTable hash_table;

public:
    plDataSet();
    plDataSet(State s);
    plDataSet(int32_t hash_table_size);
    ~plDataSet();

    plInstance get(std::string key);
    int32_t set(std::string key, std::string value);
};