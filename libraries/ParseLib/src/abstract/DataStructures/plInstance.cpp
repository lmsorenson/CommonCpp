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

plInstance plInstance::related(std::string a_label)
{
    //id 
    int32_t index_buffer = -1;

    owning_data_set->TokenizeKeys(
        this->key, 
        [&](int32_t key_i,int32_t index, string label) mutable
        {
            if(label==a_label)
            {
                index_buffer = index;
            }
        }
        );
    a_label.append(to_string(index_buffer));
    plInstance return_var = owning_data_set->get(a_label);
    return return_var;
}


void plInstance::add(std::string str_value)
{
    value.push_back(str_value);
}

void plInstance::SetKey(std::string a_key)
{
    key = a_key;
}