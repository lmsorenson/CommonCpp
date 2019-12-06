// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../instance.hpp"
#include <data_set.hpp>


using ::std::vector;
using ::std::string;
using ::std::to_string;
using ::sdg::Instance;


const std::vector<std::string>::iterator Instance::begin()
{
    return value.begin();
}

const std::vector<std::string>::iterator Instance::end()
{
    return value.end();
}


string Instance::get() const
{
    if (state == VALID_INST && value.size()!= 0)
    {
        if (value.size()==1)
        {
            return value[0];
        }
        else if(value.size()>0)
        {
            return "SPECIFY_AN_INDEX";
        }
        else
        {
            return "ERROR";
        }
    }
    else if (state == NO_FILE)
        return "NO_FILE";
    //if the value of the instance is of size 0
    else
        return "NULL";
}




std::vector<std::string> Instance::get_vector()
{
    return value;
}




string Instance::at(int8_t index) const
{
    if(state == VALID_INST && value.size()!= 0)
    {
        if(value.size()>=(index+1))
        {
            return value[index];
        }
        else
            return "NULL";
    }
    else
    {
       return "NULL";
    }
}




Instance Instance::related(string a_label) const
{ 
    //get the descriptor-index value off the entity identified
    //by 'a_label'
    string attr_buffer;
    
    
    if(get_descriptor(a_label)!="NO_VALUE")
        attr_buffer.append(get_descriptor(a_label));

    else if(!owning_data_set->IsDescriptorRequired(a_label))
        attr_buffer.append(a_label);

    //get any other descriptors that might be necessary
    vector<string> identifier = owning_data_set->get_data_model().get_entity_identifier(a_label);

    for(int i=0; i<identifier.size();++i)
    {
        if(get_descriptor(identifier[i])!="NO_VALUE")
        {
            if(!attr_buffer.empty())
                attr_buffer.append("-");

            attr_buffer.append(get_descriptor(identifier[i]));
        }
            

        else if(!owning_data_set->IsDescriptorRequired(identifier[i]))
        {
            if(!attr_buffer.empty())
                attr_buffer.append("-");

            attr_buffer.append(identifier[i]);
        }
    }

    //get the value from the associated DataSet
    return owning_data_set->get(attr_buffer);
}




//Get next instance in 'a_label'
Instance Instance::pull_next(string a_label) const
{
    // get next instance with respect to entity identified by a_label
    Instance owner;

    //1. get owning entity instance
    //2. check if the instance is valid before continuing
    if(!(owner = this->related(a_label)).is_valid())
        return Instance(owning_data_set, NULL_INST);

    //------------------------------------------
    //      step through value iterator
    //------------------------------------------
    //start at the first value in the set
    auto itr = owner.value.cbegin();
    int32_t pos=0;

    //find the current instance if it exists.
    while(((*itr)!=this->get()) && (itr!=owner.value.cend()))
    {
        itr++;
        pos++;
    }

    //check that this and the next item both exist before continuing
    if((itr!=owner.value.cend()) && (++itr!=owner.value.cend()))
    {
        vector<string> 
        missing_desc = owning_data_set->get_missing_descriptors(a_label);
        
        pos++;

        if(missing_desc.size()==1)
        {
            string generated_identifier;
            generated_identifier.append(key);
            generated_identifier.append("-");
            generated_identifier.append(missing_desc[0]);
            generated_identifier.append(to_string(pos));

            return owning_data_set->get(generated_identifier);
        }
        //todo-->so far this should never happen
        else if(missing_desc.size()>1)
        {
            return Instance(owning_data_set, NULL_INST);
        }
        else
        {
            return Instance(owning_data_set, NULL_INST);
        }
    }

    //if the next item doesn't exist then end here.
    else
        return Instance(owning_data_set, NULL_INST);
}




Instance Instance::pull_previous(string a_label) const
{

    return Instance();
}


bool Instance::is_valid() const
{
    return (state == VALID_INST);
}    



int32_t Instance::find(std::string a_value, int32_t offset) const
{
    //------------------------------------------
    //      step through value iterator
    //------------------------------------------
    //start at the first value in the set
    auto itr = this->value.cbegin();
    int32_t pos=offset;

    //find the current instance if it exists.
    while(( (itr!=this->value.cend()) && (*itr)!=a_value))
    {
        itr++;
        pos++;
    }

    return pos;
}


string Instance::get_descriptor(string a_label) const
{
    string desc_buffer = a_label;
    int32_t index_buffer = -1;

    owning_data_set->id_lexer(
        this->key, 
        [&](int32_t key_i,int32_t index, string found_label) mutable
        {
            if(found_label==desc_buffer)
            {
                index_buffer = index;
            }
        }
        );

    if (index_buffer!=-1)
        desc_buffer.append(to_string(index_buffer));
    else
        return "NO_VALUE";

    return desc_buffer;
}