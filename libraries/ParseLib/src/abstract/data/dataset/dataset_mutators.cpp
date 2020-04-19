// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <objects/data_set.hpp>



using std::string;
using std::vector;
using std::function;
using std::make_shared;


sdg::hash::DescriptorInstance get_matching_descriptor(sdg::hash::KeyInstance a_key, sdg::hash::DescriptorID a_descriptor_id);

int32_t sdg::DataSet::set(hash::KeyInstance a_key, plHashValue a_value)
{
    switch (state)
    {
    case DATA_SET_EMPTY: 
        state = DATA_SET_GOOD; //Empty data sets should also implement DATA_SET_GOOD protecol
    case DATA_SET_GOOD: 
        //todo -- investigate difference between key and subset key.
        hash_table.insert(a_key, plHashValue(a_value));
        this->update_descriptor_counts(a_key);
        return 0; 
        break;
    case DATA_SET_BAD: return DATA_SET_BAD; break;
    default:
    case UNKNOWN: return UNKNOWN; break;
    }
}



int32_t sdg::DataSet::set(hash::KeyInstance a_key, plHashValue a_value, hash::DescriptorID a_descriptor_id)
{
    plHashValue replaced_value;
    hash::KeyInstance new_key;

    hash::DescriptorID copy_descriptor_id = a_descriptor_id;
    hash::DescriptorInstance new_descriptor;

    switch (state)
    {
    case DATA_SET_EMPTY: 
        state = DATA_SET_GOOD; //Empty data sets should also implement DATA_SET_GOOD protecol
    case DATA_SET_GOOD: 

        //returns a copy of the value that was replaced in the operation.
        replaced_value = hash_table.insert(a_key, plHashValue(a_value));

        //maintains count for the list
        this->update_descriptor_counts(a_key);

        if(replaced_value.is_valid())
        {
            //
            new_descriptor = get_matching_descriptor(a_key, copy_descriptor_id);
            
            new_key = increment_descriptor_in_key(new_descriptor, a_key, 0);

            replaced_value = hash_table.insert(new_key, plHashValue(replaced_value));
            
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





// int32_t sdg::DataSet::register_descriptor(std::string a_new_descriptor)
// {
//     expected_descriptors.push_back(make_shared<EntityKey>(EntityKey(a_new_descriptor)));

//     return 0;
// }

// int32_t sdg::DataSet::add_optional_flag(std::string a_new_descriptor)
// {
//     expected_descriptors.push_back(make_shared<EntityKey>(EntityKey(a_new_descriptor, false, false)));

//     return 0;
// }





void sdg::DataSet::add_instance(hash::EntityID entity_id, std::vector<std::string> entity_values, int32_t position)
{
    //todo-->handle definition of this function
}

void sdg::DataSet::remove_instance(hash::KeyInstance a_key_subset)
{
    //todo-->handle definition of this function
}

void sdg::DataSet::reposition_instance(hash::DescriptorInstance a_descriptor, int32_t position)
{
    //todo-->handle definition of this function
}






void sdg::DataSet::update_descriptor_counts(hash::KeyInstance a_key)
{
    std::string copy = a_key.as_string();
    
    auto function = [&](const std::string callback_token)
    {
        char scanned_descriptor_id[1];
        int32_t scanned_descriptor_value;
        sscanf(callback_token.c_str(), "%1s%i", scanned_descriptor_id, &scanned_descriptor_value);

        auto descriptor = hash::DescriptorInstance(scanned_descriptor_id, Attribute::Scale::Numeric);
        descriptor.set_value(scanned_descriptor_value);
    
        logical_data_structure.found_descriptor(descriptor);
    };

    a_key.for_each_descriptor(function);
}


//gets a copy of the descriptor within a key matching the descriptor id if one exists.
sdg::hash::DescriptorInstance get_matching_descriptor(sdg::hash::KeyInstance a_key, sdg::hash::DescriptorID a_descriptor_id)
{
    using namespace sdg::hash;

    KeyInstance copy = a_key;

    DescriptorInstance local_descriptor = DescriptorInstance("NULL", sdg::Attribute::Scale::Numeric);

    auto function = [&](const std::string callback_token)
    {
        if(std::string(callback_token).substr(0,1).compare(a_descriptor_id.as_string())==0)
        {
            DescriptorInstance descriptor = DescriptorInstance(std::string(callback_token).substr(0,1), sdg::Attribute::Scale::Numeric);
            descriptor.set_value(std::stoi(std::string(callback_token).substr(1,1)));

            local_descriptor=descriptor;
            return;
        }
    };

    copy.for_each_descriptor(function);

    return local_descriptor;
}
