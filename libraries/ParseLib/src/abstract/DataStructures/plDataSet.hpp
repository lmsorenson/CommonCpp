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

    class EntityKey
    {
        std::string label;
        int32_t index;

    public:
        EntityKey();
        EntityKey(std::string label);
        ~EntityKey();

        std::string GetLabel();
        int32_t SetIndex(int32_t a_index);
        int32_t GetIndex();
    };

    //a hash table to store the data in.
    hTable hash_table;
    std::vector<std::shared_ptr<plDataSet::EntityKey>> recognized_key;

public:
    plDataSet();
    plDataSet(State s);
    plDataSet(int32_t hash_table_size);
    ~plDataSet();

    plInstance get(std::string aKey);
    int32_t set(std::string aKey, hValue aValue);
    int32_t add_label(std::string new_label);
};