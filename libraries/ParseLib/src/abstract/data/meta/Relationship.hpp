// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once

#include <memory>
#include <vector>
#include <string>

#include "Interface.hpp"
#include "Descriptor.hpp"


class Relationship : public Thing
{
public:
    enum IDENTIFY_BY : int8_t
    {
        NO_ID,
        LINK_1,
        LINK_2
    };


    Relationship(std::string a_name, std::shared_ptr<Entity> a_linked_entity, std::shared_ptr<Entity> a_linked_entity_2, bool a_be = false, IDENTIFY_BY ID_BY = NO_ID);
    ~Relationship()=default;

private:
    bool to_be_flag;
    ManyLink<Link> link_array;
};




