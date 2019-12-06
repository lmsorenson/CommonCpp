// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <data_set.hpp>


using ::std::string;
using ::std::to_string;
using ::std::vector;


int32_t sdg::DataSet::IsDescriptorRequired(string a_descriptor) const
{
    int32_t r=-1;

    bool b_descriptor_found = false;

    for(auto descriptor : this->expected_descriptors)
    {
        if(descriptor->GetLabel() == a_descriptor)//if this is never called return an error.
        {       
            if (b_descriptor_found)//if this is ever called return an error.
                r=-1;

            r=descriptor->IsRequired();
        }
    }

    return r;
}

int32_t sdg::DataSet::number_of_entity_instances(std::string a_entity_id)
{
    return this->logical_data_structure.get_entity_count(a_entity_id);
}

int32_t sdg::DataSet::increment_counter(std::string a_entity_id)
{
    // logical_data_structure.increment_entity_counter(a_entity_id);
    return 0;
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

    int32_t pos = ret.find(value);

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
        return sdg::Instance(this, Instance::NO_FILE);

    Instance return_var;
   
    string 
        key_buffer = a_descriptor,
        generated_key,
        result;

    bool data_missing = false;

    //buffer the expected_descriptors to avoid modifying the data set.
    std::vector<DataSet::EntityKey> expected_descriptor_buffer;
    for(int32_t i=0; i<expected_descriptors.size(); ++i)
    {
        expected_descriptor_buffer.push_back(*(expected_descriptors[i]));
    }

    return_var = sdg::Instance(this, Instance::VALID_INST);
    return_var.set_key(a_descriptor);//assign the key which was passed into this function.

    /*-----------------------------------*
    *              Lexer                 *
    * ----------------------------------*/
    key_buffer = this->id_lexer(
        key_buffer, 
        [&](int32_t key_i,int32_t index, string found_label)
        {
            if (expected_descriptor_buffer[key_i].HasIndex())
                expected_descriptor_buffer[key_i].SetIndex(index);
            else
                expected_descriptor_buffer[key_i].SetFound();
        }
        );
    
    /*-----------------------------------*
    *             Compiler               *
    * ----------------------------------*/
    for(int i=0; i<expected_descriptor_buffer.size(); ++i)
    {
        

        if(expected_descriptor_buffer[i].GetIndex()!=-1)
        {
            //add the delimiter
            if (!generated_key.empty())
                generated_key.append("-");

            //push key to the format.
            generated_key.append(expected_descriptor_buffer[i].GetLabel());
            
            if(expected_descriptor_buffer[i].HasIndex())
                generated_key.append(to_string(expected_descriptor_buffer[i].GetIndex()));
        }
        else if (!expected_descriptor_buffer[i].IsRequired())
        {
            //add the delimiter
            if (!generated_key.empty())
                generated_key.append("-");

            if (expected_descriptor_buffer[i].IsFound())
                generated_key.append(expected_descriptor_buffer[i].GetLabel());
        }
        else
        {
            //if any token returns missing record it.
            data_missing = true;
        }
    }

    //Ask the storage for all valid keys with matching descriptors.
    if (data_missing)
    {
        vector<string> matching_keys = hash_table.GetMatchingKeys(generated_key);

        for(int i=0; i<matching_keys.size(); ++i)
        {
            return_var.add_value(hash_table.get(matching_keys[i]));
        }
    }
    else
    {
        //return the value at the generated key
        return_var.add_value(hash_table.get(generated_key));
    }

    return (state==DATA_SET_GOOD)
    ? return_var
    : sdg::Instance(this, Instance::NULL_INST);
}
