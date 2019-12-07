// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include <iostream>

#include <objects/instance.hpp>
#include "../src/abstract/data/structures/plHash.hpp"
#include "../src/abstract/data/meta/DataModel.hpp"


#define NO_INDEX -1
#define END_OF_ENTITY_LIST -1

//soli deo gloria
namespace sdg {

class SelectionVisitor;
class EntitySelection;


class HashKey
{
public:
    HashKey() = default;
    HashKey(std::string a_value, bool a_is_partial_key)
    : value_(a_value)
    , is_partial_key_(a_is_partial_key)
    {}

    bool is_partial_key()
    {
        return is_partial_key_;
    }
    std::string value()
    {
        return value_;
    }

private:
    std::string value_;
    bool is_partial_key_;
};


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
    
    
    Instance get(std::string a_descriptor) const;
    
    //finds a specific instance without specifying an identifier.
    Instance where(std::string descriptor, std::string value) const;
    
    //get a copy of the metadata
    Model get_data_model() const;

    //is this descriptor required to uniquely identify a value
    //in the hash table.
    int32_t IsDescriptorRequired(std::string a_descriptor) const;
    
    //returns the number of instances of the chosen entity
    int32_t number_of_entity_instances(std::string entity_id) const;




    //Mutators//-------------------------------------------------

    //add an atomic value to the store identified by a list of descriptors
    int32_t set(std::string a_descriptor_list, plHashValue a_value);
    int32_t set(std::string a_descriptor_list, plHashValue a_value, std::string a_entity_id);

    //add an atomic value
    int32_t register_descriptor(std::string a_new_descriptor);
    int32_t add_optional_flag(std::string a_new_descriptor);  

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
    
    //descriptors used in the identifier for an atomic entity.
    //atomic refers to the smallest entity in a data set.
    //atomic entities are also the elements stored in the hash table.
    //this entity describes individual descriptors needed to identify a hash element.
    class EntityKey
    {

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

    private:
        std::string label;
        int32_t index;
        bool 
            required,
            has_index;

        bool b_found;

    };

protected:
    //the logical data structure is meta data about the data stored in this hash table.
    Model logical_data_structure;

    //a hash table to store the data in.
    plHashTable hash_table;

    /* Helpers */
    void displace_overwritten_keys( plHashValue replaced_value, std::string new_entity_id, std::string new_key);
    std::string increment_descriptor_in_key(std::string entity_id, std::string hash_key, int32_t position);
    void update_descriptor_counts(std::string a_descriptor_list);
    sdg::HashKey compile_hash_key(const std::vector<sdg::DataSet::EntityKey> expected_descriptors) const;
    void helper(std::string key_buffer, std::vector<std::shared_ptr<DataSet::EntityKey>> expected_descriptor_buffer) const;

    //epected descriptors are descriptors needed to identify a hash value.
    std::vector<std::shared_ptr<DataSet::EntityKey>> expected_descriptors;
};




}//namespace sdg