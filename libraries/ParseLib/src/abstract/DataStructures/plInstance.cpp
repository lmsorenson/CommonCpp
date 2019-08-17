// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "plInstance.hpp"
#include "plDataSet.hpp"






plInstance::plInstance(std::string aValue)
: state(VALID_INST)
{
    value.push_back(aValue);
}

plInstance::plInstance(State s)
: state(s)
{
}

plInstance::~plInstance()
{
}

std::string plInstance::get()
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
    else
    {
        return "NULL";
    }
}

plInstance plInstance::related(std::string label)
{
    plInstance return_var = owning_data_set->get(label.append("0"));



    return return_var;
}