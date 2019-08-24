// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "Hash.hpp"
#include "plInstance.hpp"


using namespace std;



class plDataSet
{
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
        int32_t ClearIndex();
    };

    //a hash table to store the data in.
    hTable hash_table;
    std::vector<std::shared_ptr<plDataSet::EntityKey>> recognized_key;

public:
    enum State : int32_t
    {
        DATA_SET_GOOD,
        DATA_SET_BAD,
        DATA_SET_EMPTY,
        UNKNOWN
    } state;

    plDataSet();
    plDataSet(State s);
    plDataSet(int32_t hash_table_size);
    ~plDataSet();

    plInstance get(std::string aKey);
    int32_t set(std::string aKey, hValue aValue);
    int32_t add_label(std::string new_label);

    void TokenizeKeys(std::string a_key, std::function<void(int32_t key_i, int32_t index, std::string label)> lambda_expr);
};