// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "plHash.hpp"
#include "plInstance.hpp"
#include "MetaLDS.hpp"


#define NO_INDEX -1


class plDataSet
{
    //descriptors used in the identifier for an atomic entity.
    //atomic refers to the smallest entity in a data set.
    //atomic entities are also the elements stored in the hash table.
    //this entity describes individual descriptors needed to identify a hash element.
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


    //expected descriptors refers to the descriptors needed or present in some hash keys.
    std::vector<std::shared_ptr<plDataSet::EntityKey>> expected_descriptors;

protected:
    //the logical data structure is meta data about the data stored in this hash table.
    Model logical_data_structure;

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
    Model get_data_model() const;
    int32_t IsLabelRequired(std::string a_label) const;

    //Mutators//-------------------------------------------------
    int32_t set(std::string a_key, plHashValue a_value);
    int32_t add_label(std::string a_new_label);
    int32_t add_optional_flag(std::string a_new_label);  
    int32_t increment_counter(std::string a_entity_label);

    virtual void add_instance(std::string entity_name, std::vector<std::string> entity_values);
    virtual int32_t pad_entity_count(std::string entity_name, int32_t a_num_blanks=1);
    

    std::string id_lexer(
        std::string a_identifier, 
        std::function<void(int32_t key_i, int32_t index, std::string label)> lambda_expr,
        std::function<void(std::string label_not_found)> lambda_expr2=nullptr,
        std::function<void(std::string label_unrecognized)> callback_unrecognized_desc=nullptr) const;
    std::vector<std::string> get_missing_descriptors(std::string a_descriptor_labels) const;
};