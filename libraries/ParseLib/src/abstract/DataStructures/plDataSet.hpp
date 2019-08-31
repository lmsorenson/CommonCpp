// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "Hash.hpp"
#include "plInstance.hpp"




class plDataSet
{
    class EntityKey
    {
        std::string label;
        int32_t index;
        bool 
            required,
            has_index;

        bool b_found;

    public:
        EntityKey();
        EntityKey(std::string a_label, bool a_required = true, bool a_has_index = true);
        ~EntityKey();

        std::string GetLabel();
        int32_t SetIndex(int32_t a_index);
        int32_t SetFound();
        bool IsFound();
        int32_t GetIndex();
        bool IsRequired();
        bool HasIndex();
    };

    //a hash table to store the data in.
    hTable hash_table;
    std::vector<std::shared_ptr<plDataSet::EntityKey>> expected_descriptors;

public:
    enum State : int32_t
    {
        DATA_SET_GOOD,
        DATA_SET_BAD,
        DATA_SET_EMPTY,
        UNKNOWN
    } state;

    plDataSet();
    plDataSet(State a_state);
    plDataSet(int32_t a_hash_table_size);
    ~plDataSet();

    plInstance get(std::string a_key);
    plInstance where(std::string descriptor, std::string value);
    int32_t set(std::string a_key, hValue a_value);
    int32_t add_label(std::string a_new_label);
    int32_t add_optional_flag(std::string a_new_label);

    std::string id_lexer(
        std::string a_identifier, 
        std::function<void(int32_t key_i, int32_t index, std::string label)> lambda_expr,
        std::function<void(std::string label_not_found)> lambda_expr2=nullptr,
        std::function<void(std::string label_unrecognized)> callback_unrecognized_desc=nullptr);
    std::vector<std::string> get_missing_descriptors(std::string a_descriptor_labels);
};