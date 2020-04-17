// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Interface.hpp"
#include "Entity.hpp"
#include "Relationship.hpp"
#include "Descriptor.hpp"


namespace hash {
    class DescriptorID;
}

namespace sdg {

class Model 
{

public:
    Model()=default;
    ~Model()=default;

    //add a thing to the data model.
    void add_thing(std::shared_ptr<Thing> a_thing);

    //get a list of descriptor IDs representing identifying descriptors of the entity specified.
    std::vector<hash::DescriptorID> get_entity_identifier(hash::DescriptorID a_descriptor_id) const;
    std::vector<std::shared_ptr<Descriptor>> get_identifier_of_granular_entity() const;

    //increment the counter for the entity specified
    void found_descriptor(hash::DescriptorID a_descriptor_id);
    int32_t get_entity_count(hash::EntityID a_entity_id) const;


private:
    ManyLink<Thing> thing_array;

    std::shared_ptr<Entity> get_entity(hash::EntityID a_entity_id) const;\
};

}// namespace sdg
