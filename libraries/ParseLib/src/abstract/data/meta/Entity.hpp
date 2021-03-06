// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once

#include <memory>
#include <vector>
#include <string>

#include "Interface.hpp"
#include "../types/types.hpp"

namespace sdg
{

class Descriptor;
class Identifier;


class Entity : public Thing
{
    ManyLink<Descriptor> descriptor_array; 
    ManyLink<Identifier> identifier_array; 

public:
    Entity(const std::string &a_entity_id, const std::string &a_name);
    ~Entity()=default;

    void add_descriptor(std::shared_ptr<Descriptor> a_descriptor, bool b_is_identifying_descriptor = false, int32_t identifier_index = 0);
    std::vector<hash::DescriptorID> get_identifying_descriptor_id_set();
    std::vector<std::shared_ptr<Descriptor>> get_identifying_descriptor_set();
};

class Identifier 
{
    OneLink<Entity> owning_entity;
    ManyLink<Descriptor> descriptor_array; 

public:
    Identifier(std::shared_ptr<Entity> a_owner);
    ~Identifier()=default;
    void add_descriptor(std::shared_ptr<Descriptor> a_descriptor);
    std::vector<hash::DescriptorID> get_descriptor_ids();
    std::vector<std::shared_ptr<Descriptor>> get_descriptors();
};

}// namespace sdg