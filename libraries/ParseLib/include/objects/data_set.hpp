// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include <iostream>

#include <objects/instance.hpp>
#include "../src/abstract/data/structures/hash_table.hpp"
#include "../src/abstract/data/meta/DataModel.hpp"

#include "../src/abstract/data/keys/keys.hpp"


#define NO_INDEX -1
#define END_OF_ENTITY_LIST -1


namespace sdg {

class SelectionVisitor;
class EntitySelection;

namespace hash{
class HashKey;
class DescriptorInstance;
}//namespace hash


class DataSet
{

public:
    enum State : int32_t
    {
        DATA_SET_GOOD,
        DATA_SET_BAD,
        DATA_SET_EMPTY,
        UNKNOWN
    } state;

    //constructors//---------------------------------------------
    DataSet();
    DataSet(State a_state);
    DataSet(int32_t a_hash_table_size);
    ~DataSet();


    Instance operator[](std::string i);



    //accessors//------------------------------------------------
    Instance get(hash::HashKey a_descriptor) const;
    
    //finds a specific instance without specifying an identifier.
    Instance where(std::string descriptor, std::string value) const;
    
    //get a copy of the metadata
    Model get_data_model() const;

    //is this descriptor required to uniquely identify a value
    //in the hash table.
    int32_t IsDescriptorRequired(std::string a_descriptor_id) const;
    
    //returns the number of instances of the chosen entity
    int32_t number_of_entity_instances(std::string entity_id) const;



    //Mutators//-------------------------------------------------
    //add an atomic value to the store identified by a list of descriptors
    int32_t set(hash::HashKey a_descriptor_list, plHashValue a_value);
    int32_t set(hash::HashKey a_descriptor_list, plHashValue a_value, std::string a_entity_id);

    //API for modifying a data set
    virtual void add_instance(std::string entity_id, std::vector<std::string> entity_values, int32_t position=END_OF_ENTITY_LIST);
    virtual void remove_instance(std::string entity_id);
    virtual void increment_instance_id(std::string entity_id, int32_t position=1);
    virtual int32_t pad_entity_count(std::string entity_id, int32_t a_num_blanks=1);



    std::string id_lexer(
        std::string a_identifier, 
        std::function<void(int32_t key_i, int32_t index, std::string label)> lambda_expr,
        std::function<void(std::string label_not_found)> lambda_expr2=nullptr,
        std::function<void(std::string label_unrecognized)> callback_unrecognized_desc=nullptr) const;
    std::vector<std::string> get_missing_descriptors(std::string a_descriptor_labels) const;

protected:
    //the logical data structure is meta data about the data stored in this hash table.
    Model logical_data_structure;

    //a hash table to store the data in.
    plHashTable hash_table;

    /* Helpers */
    void displace_overwritten_keys( plHashValue replaced_value, std::string new_entity_id, std::string new_key);
    std::string increment_descriptor_in_key(std::string entity_id, std::string hash_key, int32_t position);
    void update_descriptor_counts(std::string a_descriptor_list);
    hash::HashKey compile_hash_key(const std::vector<hash::DescriptorInstance> expected_descriptors) const;
    std::vector<hash::DescriptorInstance> helper(std::string key_buffer, std::vector<std::shared_ptr<Descriptor>> expected_descriptor_buffer) const;

    //epected descriptors are descriptors needed to identify a hash value.
    // std::vector<std::shared_ptr<hash::DescriptorID>> expected_descriptors;
};

}//namespace sdg
//soli deo gloria