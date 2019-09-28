// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "Hash.hpp"
#include "plInstance.hpp"
#include "MetaLDS.hpp"


#define NO_INDEX -1


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

        std::string GetLabel() const;
        int32_t SetIndex(int32_t a_index);
        int32_t SetFound();
        bool IsFound() const;
        int32_t GetIndex() const;
        bool IsRequired() const;
        bool HasIndex() const;
    };

    //a hash table to store the data in.
    plHashTable hash_table;
    Model logical_data_structure;
    std::vector<std::shared_ptr<plDataSet::EntityKey>> expected_descriptors;

public:
    enum State : int32_t
    {
        DATA_SET_GOOD,
        DATA_SET_BAD,
        DATA_SET_EMPTY,
        UNKNOWN
    } state;

    //constructors//---------------------------------------------
    plDataSet();
    plDataSet(State a_state);
    plDataSet(int32_t a_hash_table_size);
    ~plDataSet();

    //accessors//------------------------------------------------
    plInstance get(std::string a_key) const;
    plInstance where(std::string descriptor, std::string value) const;

    //Mutators//-------------------------------------------------
    int32_t set(std::string a_key, plHashValue a_value);
    int32_t add_label(std::string a_new_label);
    int32_t add_optional_flag(std::string a_new_label);
    int32_t generate_data_model();
    Model get_data_model() const;
    int32_t IsLabelRequired(std::string a_label) const;

    std::string id_lexer(
        std::string a_identifier, 
        std::function<void(int32_t key_i, int32_t index, std::string label)> lambda_expr,
        std::function<void(std::string label_not_found)> lambda_expr2=nullptr,
        std::function<void(std::string label_unrecognized)> callback_unrecognized_desc=nullptr) const;
    std::vector<std::string> get_missing_descriptors(std::string a_descriptor_labels) const;
};