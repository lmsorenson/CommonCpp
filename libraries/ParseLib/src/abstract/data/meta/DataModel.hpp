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

    size_t size();

    //add a thing to the data model.
    int8_t add_thing(std::shared_ptr<Thing> a_thing);

    //get a list of descriptor IDs representing identifying descriptors of the entity specified.
    std::vector<hash::DescriptorID> get_entity_identifier(hash::EntityID a_entity_id) const;
    std::vector<std::shared_ptr<Descriptor>> get_identifier_of_granular_entity() const;

    //increment the counter for the entity specified
    //todo -- these members are related to runtime instances.  These are not part of the model, they should be relocated.
    void found_descriptor(hash::DescriptorInstance a_descriptor);

    /**
     *
     * @param a_entity_id is a unique identifier for the entity in the model.
     * @return a number of instances of the entity.
     */
    int32_t get_entity_count(hash::EntityID a_entity_id) const;
    
private:
    ManyLink<Thing> thing_array_;
    ::std::vector<::std::string> key_array_;

    /**
     *
     * @param a_entity_id is a unique identifier for the entity in the model.
     * @return a pointer to an entity meta object.
     */
    std::shared_ptr<Entity> get_entity(hash::EntityID a_entity_id) const;
};

}// namespace sdg
