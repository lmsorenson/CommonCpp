// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>




class plDataSet;

class plInstance
{
    plDataSet * owning_data_set;
    std::vector<plInstance> relationship;
    std::string key;//the key that identifies this instance
    std::vector<std::string> value;//the values stored.

public:
    enum State : int32_t
    {
        VALID_INST,
        NULL_INST,
        NO_FILE,
        UNKNOWN
    } state;

    plInstance() = default;
    plInstance(plDataSet * owner, State s);
    ~plInstance();

    std::string get();
    std::string at(int8_t index);
    plInstance related(std::string a_label);

    void add(std::string str_value);//add a value
    void SetKey(std::string a_key);//assign the key
};