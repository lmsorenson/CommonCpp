// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "plInstance.hpp"
#include "plDataSet.hpp"
#include <iostream>





using namespace std;

plInstance::plInstance(State s)
: state(s)
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
    //if the value of the instance is of size 0
    else
    {
        return "NULL";
    }
}
string plInstance::get(int8_t index)
{
    if(state == VALID_INST && value.size()!= 0)
    {
        if(value.size()>=index)
            return value[index];
        else
            return "ERROR";
    }
    else
    {
       return "NULL";
    }
}

plInstance plInstance::related(std::string a_label)
{
    //id 
    owning_data_set->TokenizeKeys(
        this->key, 
        [=](int32_t key_i,int32_t index, string label)
        {
            if(label==a_label)
            {
                cout << "hey" << endl;
            }
        }
        );

    plInstance return_var = owning_data_set->get(a_label.append("0"));
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