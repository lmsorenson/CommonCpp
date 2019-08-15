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
    return (state == VALID_INST)
    ? value[0]
    : "NULL";
}

plInstance plInstance::related(std::string label)
{
    return owning_data_set->get(label.append("0"));
}