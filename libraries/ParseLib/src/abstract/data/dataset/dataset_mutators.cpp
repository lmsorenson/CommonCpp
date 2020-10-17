// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <objects/data_set.hpp>



using ::std::string;
using ::std::vector;
using ::std::function;
using ::std::make_shared;
using ::sdg::hash::DescriptorID;
using ::sdg::hash::DescriptorInstance;
using ::sdg::hash::KeyInstance;
using ::sdg::hash::EntityID;
using ::sdg::DataSet;
using ::sdg::Attribute;

/**
 * gets a copy of the descriptor within a key matching the descriptor id if one exists.
 * @param a_key
 * @param a_descriptor_id
 * @return
 */
DescriptorInstance get_matching_descriptor(KeyInstance a_key, DescriptorID a_descriptor_id);

/**
 * Adds an element to the dataset if the dataset is in a good state.
 * @param a_key The key for the element.
 * @param a_value The element value to add to the dataset.
 * @return A status code for the operation.
 */
int32_t DataSet::set(KeyInstance a_key, plHashValue a_value)
{
    if (a_key.is_default())
        return -1;

    switch (state_)
    {
    case DATA_SET_EMPTY:
        state_ = DATA_SET_GOOD; //Empty data sets should also implement DATA_SET_GOOD protocol.
    case DATA_SET_GOOD:
        //todo -- investigate difference between key and subset key.
        hash_table_.insert(a_key, plHashValue(a_value));
        //todo -- the following function call is linked to a crash if called
        //on a generic dataset
        this->update_descriptor_counts(a_key);
        return 0;
        break;
    case DATA_SET_BAD: return DATA_SET_BAD; break;
    default:
    case UNKNOWN: return UNKNOWN; break;
    }
}

/**
 * Adds an element to the dataset, displaces the next element if one exists at the keyed location.
 * @param a_key The keyed location to add to the dataset.
 * @param a_value The The element value to add to the dataset.
 * @param a_descriptor_id The descriptor id for the dimension used to displace replaced objects.
 * @return A status code for the operation.
 */
int32_t DataSet::set(KeyInstance a_key, plHashValue a_value, DescriptorID a_descriptor_id)
{
    if (a_key.is_default())
        return -1;

    plHashValue replaced_value;
    KeyInstance new_key;
    DescriptorInstance new_descriptor;

    switch (state_)
    {
    case DATA_SET_EMPTY:
        state_ = DATA_SET_GOOD; //Empty data sets should also implement DATA_SET_GOOD protocol.
    case DATA_SET_GOOD: 

        //returns a copy of the value that was replaced in the operation.
        replaced_value = hash_table_.insert(a_key, plHashValue(a_value));

        //maintains count for the list
        this->update_descriptor_counts(a_key);

        if(replaced_value.is_valid())
        {
            new_descriptor = get_matching_descriptor(a_key, a_descriptor_id);
            
            new_key = increment_descriptor_in_key(new_descriptor, a_key, 0);

            replaced_value = hash_table_.insert(new_key, plHashValue(replaced_value));
            
            this->update_descriptor_counts(new_key);
            
            //recursively replaces elements that are over written.
            displace_overwritten_keys(replaced_value, new_descriptor, new_key);
        }
        
        return 0; 
        break;
    case DATA_SET_BAD: return DATA_SET_BAD; break;
    default:
    case UNKNOWN: return UNKNOWN; break;
    }
}

/**
 *
 * @param a_entity_id
 * @param a_entity_values
 * @param a_position
 */
void DataSet::add_instance(EntityID a_entity_id, vector<string> a_entity_values, int32_t a_position)
{
    //todo-->handle definition of this function
}

/**
 * Removes an element from the dataset.
 * @param a_key_subset A unique identifier for the element to be removed.
 */
void DataSet::remove_instance(KeyInstance a_key_subset)
{
    //todo-->handle definition of this function
}

/**
 * Base implementation for the reposition instance.
 * @param a_descriptor
 * @param a_position
 */
void DataSet::reposition_instance(DescriptorInstance a_descriptor, int32_t a_position)
{
    //todo-->handle definition of this function
}

/**
 *
 * @param a_key
 */
void DataSet::update_descriptor_counts(KeyInstance a_key)
{
    //defines the procedure to run on every descriptor in the key.
    auto function = [&](const string &callback_token)
    {
        char scanned_descriptor_id[1];
        int32_t scanned_descriptor_value;
        sscanf(callback_token.c_str(), "%1s%i", scanned_descriptor_id, &scanned_descriptor_value);

        auto local_descriptor = DescriptorInstance(scanned_descriptor_id, Attribute::Scale::Numeric);
        local_descriptor.set_value(scanned_descriptor_value);
    
        this->logical_data_structure.found_descriptor(local_descriptor);
    };

    //runs function in every descriptor.
    a_key.for_each_descriptor(function);
}

/**
 * Gets a copy of the descriptor within a key matching the descriptor id if one exists.
 * @param a_key A key
 * @param a_descriptor_id
 * @return
 */
DescriptorInstance get_matching_descriptor(KeyInstance a_key, DescriptorID a_descriptor_id)
{
    using namespace sdg::hash;

    DescriptorInstance local_descriptor = DescriptorInstance("NULL", Attribute::Scale::Numeric);

    auto function = [&](const std::string callback_token)
    {
        if(string(callback_token).substr(0,1).compare(a_descriptor_id.as_string())==0)
        {
            DescriptorInstance descriptor = DescriptorInstance(string(callback_token).substr(0,1), sdg::Attribute::Scale::Numeric);
            descriptor.set_value(std::stoi(std::string(callback_token).substr(1,1)));

            local_descriptor=descriptor;
            return;
        }
    };

    a_key.for_each_descriptor(function);

    return local_descriptor;
}
