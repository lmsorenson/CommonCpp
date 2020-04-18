// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <objects/data_set.hpp>



using std::string;
using std::vector;
using std::function;
using std::make_shared;


sdg::hash::DescriptorInstance get_matching_descriptor(sdg::hash::KeyInstance a_key, sdg::hash::DescriptorID a_descriptor_id);

int32_t sdg::DataSet::set(hash::KeyInstance a_descriptor_list, plHashValue a_value)
{
    switch (state)
    {
    case DATA_SET_EMPTY: 
        state = DATA_SET_GOOD; //Empty data sets should also implement DATA_SET_GOOD protecol
    case DATA_SET_GOOD: 
        hash_table.insert(a_descriptor_list.as_string(), plHashValue(a_value));
        this->update_descriptor_counts(a_descriptor_list.as_string());
        return 0; 
        break;
    case DATA_SET_BAD: return DATA_SET_BAD; break;
    default:
    case UNKNOWN: return UNKNOWN; break;
    }
}



int32_t sdg::DataSet::set(hash::KeyInstance a_descriptor_list, plHashValue a_value, hash::DescriptorID a_descriptor_id)
{
    plHashValue replaced_value;
    std::string new_key;

    hash::DescriptorID copy_descriptor_id = a_descriptor_id;
    hash::DescriptorInstance new_descriptor;

    switch (state)
    {
    case DATA_SET_EMPTY: 
        state = DATA_SET_GOOD; //Empty data sets should also implement DATA_SET_GOOD protecol
    case DATA_SET_GOOD: 

        //returns a copy of the value that was replaced in the operation.
        replaced_value = hash_table.insert(a_descriptor_list.as_string(), plHashValue(a_value));

        //maintains count for the list
        this->update_descriptor_counts(a_descriptor_list.as_string());

        if(replaced_value.is_valid())
        {
            //
            new_descriptor = get_matching_descriptor(a_descriptor_list, copy_descriptor_id);
            
            new_key = increment_descriptor_in_key(new_descriptor, a_descriptor_list.as_string(), 0);

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
    char * token = strtok((char*)copy.c_str(),"-");

    while(token!=NULL)
    {
        logical_data_structure.found_descriptor(hash::DescriptorID(token));

        token = strtok(NULL,"-");
    }
}


//gets a copy of the descriptor within a key matching the descriptor id if one exists.
sdg::hash::DescriptorInstance get_matching_descriptor(sdg::hash::KeyInstance a_key, sdg::hash::DescriptorID a_descriptor_id)
{
    using namespace sdg::hash;

    KeyInstance copy = a_key;

    char * token = strtok((char*)copy.as_string().c_str(),"-");

    while(token!=NULL)
    {
        if(std::string(token).substr(0,1).compare(a_descriptor_id.as_string())==0)
        {
            DescriptorInstance descriptor = DescriptorInstance(std::string(token).substr(0,1), sdg::Attribute::Scale::Numeric);
            descriptor.set_value(std::stoi(std::string(token).substr(1,1)));

            return descriptor;
        }

        token = strtok(NULL,"-");
    }

    return DescriptorInstance("NULL", sdg::Attribute::Scale::Numeric);
}
