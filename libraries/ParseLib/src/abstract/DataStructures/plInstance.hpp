// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <string>


class plInstance
{
    
    std::string entity_label, entity_index, value;

public:
    enum State: int32_t
    {
        VALID_INST,
        NULL_INST,
        UNKNOWN
    } state;

    plInstance(std::string aValue);
    plInstance(State s);
    ~plInstance();

    std::string get();
};