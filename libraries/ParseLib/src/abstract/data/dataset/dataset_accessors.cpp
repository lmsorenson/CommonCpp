// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <objects/data_set.hpp>

#include "../types/types.hpp"


using ::std::string;
using ::std::to_string;
using ::std::vector;
using ::std::shared_ptr;
using ::std::dynamic_pointer_cast;
using ::std::make_shared;
using ::sdg::Model;

/**
 * Checks if the descriptor specified is required.
 * @param a_descriptor_id A unique identifier for the descriptor to locate.
 * @return True, false, or error:  1 = true, 0 = false, -1 = error
 */
int32_t sdg::DataSet::is_descriptor_required(hash::DescriptorID a_descriptor_id) const
{
    //go through IDs of all expected descriptors
    for( auto descriptor : this->logical_data_structure.get_identifier_of_granular_entity() )
    {
        // =>
        //if the current descriptor is a match with the argument...
        if(descriptor->get_id() == a_descriptor_id.as_string())//if this is never called return an error.
        {
            std::shared_ptr<Attribute> attribute = dynamic_pointer_cast<Attribute>(descriptor);

            return ( attribute && ( attribute->get_scale() != Attribute::Scale::Boolean ) );
        }
    }

    //if the program gets through all descriptors without finding a match then there was an error.
    return -1;
}

int32_t sdg::DataSet::number_of_entity_instances(hash::EntityID a_entity_id) const
{
    return this->logical_data_structure.get_entity_count(a_entity_id);
}

Model sdg::DataSet::get_data_model() const
{
    return logical_data_structure;
}

/**
 * Finds a complete set of descriptors, for a descriptor subset where the associated value matches
 * some expected value.
 * @param a_key_subset An identifier for another entity which identifies the granular entity.
 * @param expected_value The value expected.
 * @return Return an instance.
 */
sdg::Instance sdg::DataSet::where(hash::KeyInstance a_key_subset, std::string expected_value) const
{
    Instance keyed_instance;

    //get the keyed instanced, if it doesn't exist return a null instance.
    if ( !(keyed_instance = this->get(a_key_subset)).is_valid() )
        return sdg::Instance(this, sdg::Instance::NULL_INST);

    //todo --> error prone: it depends on ordinal descriptors with indexes
    // starting at 0.
    int32_t pos = keyed_instance.find_index_of(expected_value);

    vector<string> missing_desc = this->get_missing_descriptors(a_key_subset);        

    //todo --> needs to be verified, presumably it is necessary to leave only
    // one missing descriptor.
    if( missing_desc.size() == 1 )
    {
        string generated_identifier;
        generated_identifier.append(missing_desc[0]);
        generated_identifier.append(to_string(pos));

        return this->get(hash::KeyInstance(generated_identifier));
    }

    //todo --> error prone: if multiple descriptors are unspecified
    // the specific instance cannot be resolved.
    else if( missing_desc.size() > 1 )
    {
        return sdg::Instance(this, Instance::NULL_INST);
    }
    else
    {
        return sdg::Instance(this, Instance::NULL_INST);
    }
}


sdg::Instance sdg::DataSet::get(hash::KeyInstance a_descriptor_list) const
{
    if (state_ == DATA_SET_BAD)
        return Instance(this, Instance::NO_FILE);

    //initializing a valid instance return buffer.
    Instance return_buffer = Instance(this, Instance::VALID_INST, a_descriptor_list);

    //get a set of descriptors from a list of expected descriptor IDs
    std::vector<hash::DescriptorInstance> expected_descriptor_buffer = get_descriptors_from_descriptor_id_set(a_descriptor_list, this->logical_data_structure.get_identifier_of_granular_entity());

    //try to compile the hash key
    hash::KeyInstance generated_key = compile_hash_key(expected_descriptor_buffer);

    //does this key contain all necessary descriptors for a query?
    if ( generated_key.is_partial_key() )
    {
        vector<hash::KeyInstance> matching_keys = hash_table_.GetMatchingKeys(generated_key);
        for(int i=0; i<matching_keys.size(); ++i)
        {
            return_buffer.add_value(hash_table_.get(matching_keys[i]));
        }
    }
    else 
    {
        //return the value at the generated key
        return_buffer.add_value(hash_table_.get(generated_key));
    }
        
    

    return (state_ == DATA_SET_GOOD)

    //success
    ? return_buffer

    //failure
    : sdg::Instance(this, Instance::NULL_INST);
}