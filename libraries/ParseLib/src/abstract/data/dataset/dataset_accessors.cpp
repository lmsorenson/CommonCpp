// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <objects/data_set.hpp>

#include "../keys/keys.hpp"


using ::std::string;
using ::std::to_string;
using ::std::vector;
using ::std::shared_ptr;
using ::std::dynamic_pointer_cast;
using ::std::make_shared;


int32_t sdg::DataSet::IsDescriptorRequired(string a_descriptor_id) const
{
    int32_t r=-1;

    bool b_descriptor_found = false;

    //go through IDs of all expected descriptors
    for( auto descriptor : this->logical_data_structure.get_identifier_of_granular_entity() )
    {
        //if the current descriptor is a match with the argument...
        if(descriptor->get_id() == a_descriptor_id)//if this is never called return an error.
        {       
            if (b_descriptor_found)//if this is ever called return an error.
                r=-1;

            std::shared_ptr<Attribute> attribute = dynamic_pointer_cast<Attribute>(descriptor);

            r=( attribute && (attribute->get_scale() != Attribute::Scale::Boolean) );
        }
    }

    return r;
}

int32_t sdg::DataSet::number_of_entity_instances(std::string a_entity_id) const
{
    return this->logical_data_structure.get_entity_count(a_entity_id);
}

Model sdg::DataSet::get_data_model() const
{
    return logical_data_structure;
}


sdg::Instance sdg::DataSet::where(std::string descriptor, std::string value) const
{
    Instance ret;

    //1. get owning entity instance
    //2. check if the instance is valid before continuing
    if(!(ret = this->get(descriptor)).is_valid())
        return sdg::Instance(this, sdg::Instance::NULL_INST);

    int32_t pos = ret.FindIndexOfValue(value);

    vector<string> missing_desc = this->get_missing_descriptors(descriptor);        

    if(missing_desc.size()==1)
    {
        string generated_identifier;
        generated_identifier.append(missing_desc[0]);
        generated_identifier.append(to_string(pos));

        return this->get(generated_identifier);
    }
    //todo-->so far this should never happen
    else if(missing_desc.size()>1)
    {
        return sdg::Instance(this, Instance::NULL_INST);
    }
    else
    {
        return sdg::Instance(this, Instance::NULL_INST);
    }
}


sdg::Instance sdg::DataSet::get(std::string a_descriptor) const
{
    if (state == DATA_SET_BAD)
        return Instance(this, Instance::NO_FILE);

    //initializing a valid instance return buffer.
    Instance return_buffer = Instance(this, Instance::VALID_INST, a_descriptor);

    //get a set of descriptors from a list of expected descriptor IDs
    std::vector<hash::DescriptorInstance> 
        expected_descriptor_buffer = helper(a_descriptor, this->logical_data_structure.get_identifier_of_granular_entity());

    //try to compile the hash key
    hash::HashKey generated_key = compile_hash_key(expected_descriptor_buffer);

    //does this key contain all necessary descriptors for a query?
    if ( generated_key.is_partial_key() )
    {
        vector<string> matching_keys = hash_table.GetMatchingKeys(generated_key.value());
        for(int i=0; i<matching_keys.size(); ++i)
        {
            return_buffer.add_value(hash_table.get(matching_keys[i]));
        }
    }
    else 
    {
        //return the value at the generated key
        return_buffer.add_value(hash_table.get(generated_key.value()));
    }
        
    

    return (state==DATA_SET_GOOD)

    //success
    ? return_buffer

    //failure
    : sdg::Instance(this, Instance::NULL_INST);
}