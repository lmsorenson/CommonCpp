// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "plInstance.hpp"
#include "plDataSet.hpp"
#include <iostream>





using namespace std;

plInstance::plInstance(plDataSet * owner, State s)
: owning_data_set(owner)
, state(s)
{
}

plInstance::~plInstance()
{
}

string plInstance::get()
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
string plInstance::at(int8_t index)
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

plInstance plInstance::related(string a_label)
{ 
    //get the descriptor-index value off the entity identified
    //by 'a_label'
    string attr_buffer = get_descriptor(a_label);

    //get the value from the associated plDataSet
    return owning_data_set->get(attr_buffer);
}

//Get next instance in 'a_label'
plInstance plInstance::pull_next(string a_label)
{
    // get next instance with respect to entity identified by a_label
    plInstance owner;

    //1. get owning entity instance
    //2. check if the instance is valid before continuing
    if(!(owner = this->related(a_label)).is_valid())
        return plInstance(owning_data_set, NULL_INST);

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
            return plInstance(owning_data_set, NULL_INST);
        }
        else
        {
            return plInstance(owning_data_set, NULL_INST);
        }
    }

    //if the next item doesn't exist then end here.
    else
        return plInstance(owning_data_set, NULL_INST);
}

plInstance plInstance::pull_previous(string a_label)
{

    return plInstance();
}

bool plInstance::is_valid()
{
    return (state == VALID_INST);
}    


int32_t plInstance::find(std::string a_value, int32_t offset)
{
    //------------------------------------------
    //      step through value iterator
    //------------------------------------------
    //start at the first value in the set
    auto itr = this->value.cbegin();
    int32_t pos=offset;

    //find the current instance if it exists.
    while(((*itr)!=a_value) && (itr!=this->value.cend()))
    {
        itr++;
        pos++;
    }

    return pos;
}


void plInstance::add(std::string str_value)
{
    value.push_back(str_value);
}

void plInstance::SetKey(std::string a_key)
{
    key = a_key;
}


string plInstance::get_descriptor(string a_label)
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

    desc_buffer.append(to_string(index_buffer));

    return desc_buffer;
}