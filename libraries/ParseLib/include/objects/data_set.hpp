// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include <iostream>

#include <objects/instance.hpp>
#include "../src/abstract/data/structures/hash_table.hpp"
#include "../src/abstract/data/meta/DataModel.hpp"

#include "../src/abstract/data/types/types.hpp"


#define NO_INDEX -1
#define END_OF_ENTITY_LIST -1





namespace sdg {

struct option;

class SelectionVisitor;
class EntitySelection;

namespace hash{
class KeyInstance;
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


    DataSet Read(std::string a_path, int32_t *status_code=nullptr);
    DataSet Read(std::string a_path, std::vector<option> read_options, int32_t * status_code=nullptr);
    void Write(std::string a_path, int32_t * status_code=nullptr);
    void Write(std::string a_path, std::vector<option> write_options, int32_t * status_code=nullptr);
    


    //accessors//------------------------------------------------
    Instance get(hash::KeyInstance a_key_subset) const;
    
    //finds a specific instance without specifying an identifier.
    Instance where(hash::KeyInstance a_key_subset, std::string value) const;
    
    //get a copy of the metadata
    Model get_data_model() const;

    //is this descriptor required to uniquely identify a value
    //in the hash table.
    int32_t IsDescriptorRequired(hash::DescriptorID a_descriptor_id) const;
    
    //returns the number of instances of the chosen entity
    int32_t number_of_entity_instances(hash::EntityID entity_id) const;



    //Mutators//-------------------------------------------------
    //add an atomic value to the store identified by a list of descriptors
    int32_t set(hash::KeyInstance a_descriptor_list, plHashValue a_value);
    int32_t set(hash::KeyInstance a_descriptor_list, plHashValue a_value, hash::DescriptorID a_descriptor_id);

    //API for modifying a data set
    virtual void add_instance(hash::EntityID entity_id, std::vector<std::string> entity_values, int32_t position=END_OF_ENTITY_LIST);
    
    //removes an entity instance
    virtual void remove_instance(hash::KeyInstance a_key_subset);

    //moves an instance along a dimension
    //increases the position of the entity in the list.
    virtual void reposition_instance(hash::DescriptorInstance a_descriptor, int32_t position=1);


    //todo -- refactor this ugly function
    std::string id_lexer(
        std::string a_identifier, 
        std::function<void(int32_t key_i, int32_t index, std::string label)> lambda_expr,
        std::function<void(std::string label_not_found)> lambda_expr2=nullptr,
        std::function<void(std::string label_unrecognized)> callback_unrecognized_desc=nullptr) const;

    std::vector<std::string> get_missing_descriptors(hash::KeyInstance a_key_subset) const;

protected:
    //the logical data structure is meta data about the data stored in this hash table.
    Model logical_data_structure;

    //a hash table to store the data in.
    plHashTable hash_table;

    /* Helpers */
    //overwrites an entity record.  recursively repositions all overwritten elements
    void displace_overwritten_keys( plHashValue replaced_value, hash::DescriptorInstance a_descriptor, hash::KeyInstance new_key);

    //increments the value on a specified numeric descriptor by 1, applys the change to the key
    std::string increment_descriptor_in_key(hash::DescriptorInstance a_descriptor, hash::KeyInstance hash_key, int32_t position);

    //takes in a full key, checks each descriptor 
    //to see if this value is greater than the current
    //count for that entity
    void update_descriptor_counts(hash::KeyInstance a_key);

    //takes a list of descriptors, compiles existing descriptors in the key format.
    //ignores booleans, returns a KeyInstance.  If assigns it as a partial key if there are descriptor values missing.
    hash::KeyInstance compile_hash_key(const std::vector<hash::DescriptorInstance> expected_descriptors) const;

    //todo -- what does this function do?
    std::vector<hash::DescriptorInstance> helper(hash::KeyInstance key_buffer, std::vector<std::shared_ptr<Descriptor>> expected_descriptor_buffer) const;
};

}//namespace sdg
//soli deo gloria