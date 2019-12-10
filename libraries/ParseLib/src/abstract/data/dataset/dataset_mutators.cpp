// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <objects/data_set.hpp>



using std::string;
using std::vector;
using std::function;
using std::make_shared;


std::string get_matching_descriptor(std::string a_descriptor_list, std::string a_meta_entity_id);

int32_t sdg::DataSet::set(hash::KeyInstance a_descriptor_list, plHashValue a_value)
{
    switch (state)
    {
    case DATA_SET_EMPTY: 
        state = DATA_SET_GOOD; //Empty data sets should also implement DATA_SET_GOOD protecol
    case DATA_SET_GOOD: 
        hash_table.insert(a_descriptor_list.value(), plHashValue(a_value));
        this->update_descriptor_counts(a_descriptor_list.value());
        return 0; 
        break;
    case DATA_SET_BAD: return DATA_SET_BAD; break;
    default:
    case UNKNOWN: return UNKNOWN; break;
    }
}



int32_t sdg::DataSet::set(hash::KeyInstance a_descriptor_list, plHashValue a_value, std::string a_entity_id)
{
    plHashValue replaced_value;
    std::string new_entity_id, new_key, copy_entity_id = a_entity_id;

    switch (state)
    {
    case DATA_SET_EMPTY: 
        state = DATA_SET_GOOD; //Empty data sets should also implement DATA_SET_GOOD protecol
    case DATA_SET_GOOD: 


        replaced_value = hash_table.insert(a_descriptor_list.value(), plHashValue(a_value));
        this->update_descriptor_counts(a_descriptor_list.value());

        if(replaced_value.is_valid())
        {
            new_entity_id = get_matching_descriptor(a_descriptor_list.value(), copy_entity_id);
            
            new_key = increment_descriptor_in_key(new_entity_id, a_descriptor_list.value(), 0);

            replaced_value = hash_table.insert(new_key, plHashValue(replaced_value));
            
            this->update_descriptor_counts(new_key);
            
            displace_overwritten_keys(replaced_value, new_entity_id, new_key);
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





void sdg::DataSet::add_instance(std::string entity_id, std::vector<std::string> entity_values, int32_t position)
{
    //todo-->handle definition of this function
}

void sdg::DataSet::remove_instance(std::string entity_id)
{
    //todo-->handle definition of this function
}

void sdg::DataSet::increment_instance_id(std::string entity_id, int32_t position)
{
    //todo-->handle definition of this function
}

int32_t sdg::DataSet::pad_entity_count(std::string entity_id, int32_t a_num_blanks)
{
    //todo-->handle definition of this function
    return 0;
}





void sdg::DataSet::update_descriptor_counts(std::string a_descriptor_list)
{
    std::string copy = a_descriptor_list;
    char * token = strtok((char*)copy.c_str(),"-");

    while(token!=NULL)
    {
        logical_data_structure.found_descriptor(token);

        token = strtok(NULL,"-");
    }
}

std::string get_matching_descriptor(std::string a_descriptor_list, std::string a_meta_entity_id)
{
    std::string copy = a_descriptor_list;
    char * token = strtok((char*)copy.c_str(),"-");

    while(token!=NULL)
    {
        if(std::string(token).substr(0,1).compare(a_meta_entity_id)==0)
        {
            return token;
        }

        token = strtok(NULL,"-");
    }

    return "NULL";
}
