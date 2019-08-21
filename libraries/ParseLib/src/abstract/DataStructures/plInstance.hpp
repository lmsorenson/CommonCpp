// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>




class plDataSet;

class plInstance
{
    std::shared_ptr<plDataSet> owning_data_set;
    std::vector<plInstance> relationship;
    std::string entity_label, entity_index;
    std::vector<std::string> value;

public:
    enum State : int32_t
    {
        VALID_INST,
        NULL_INST,
        UNKNOWN
    } state;

    plInstance() = default;
    plInstance(State s);
    ~plInstance();

    std::string get();
    std::string get(int8_t index);
    plInstance related(std::string label);

    void add(std::string str_value);
};