// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <iostream>

#include "../DataModel.hpp"
#include "../Relationship.hpp"
#include "../Entity.hpp"
#include "../../types/types.hpp"


using std::shared_ptr;
using std::vector;
using std::string;
using std::dynamic_pointer_cast;
using sdg::Model;
using sdg::Entity;
using sdg::Descriptor;

size_t Model::size()
{
    return thing_array_.size();
}

/**
 * Adds a thing to the model.
 * @param a_thing thing to add to the model.
 * @return 0 if the operation succeeded, 1 if the operation failed.
 */
int8_t Model::add_thing(shared_ptr<Thing> a_thing)
{
    //if the key can be found in the array do not add it again.
    if (::std::find(key_array_.begin(), key_array_.end(), a_thing->get_id()) == key_array_.end())
    {
        thing_array_.push_back(a_thing);
        key_array_.push_back(a_thing->get_id());
        return 0;
    }
    else
    {
        //error code
        return 1;
    }
}

shared_ptr<Entity> Model::get_entity(sdg::hash::EntityID a_entity_id) const
{
    shared_ptr<Entity> result;

    //get the entity.
    for(auto thing : this->thing_array_)
    {
        shared_ptr<Entity> found_entity = nullptr;

        //thing is an entity and the label matches the argument label.
        if((found_entity=dynamic_pointer_cast<Entity>(thing)))
        {
            if (a_entity_id==found_entity->get_id())
            {
                //if the found entity doesn't exist.
                if(!result)
                    result = found_entity;

                //if it does exist there has been an error.
                //no two entities should have the same id_label.
                else
                    return nullptr;
            }

        }
        
    }

    return result;
}

vector<sdg::hash::DescriptorID> Model::get_entity_identifier(hash::EntityID a_entity_id) const
{
    vector<hash::DescriptorID> identifying_descriptors;

    //select the entity.
    shared_ptr<Entity> e = get_entity(a_entity_id);

    //ask the entity for it's identifying descriptors.
    if (e!=nullptr)
        identifying_descriptors=e->get_identifying_descriptor_id_set();

    return identifying_descriptors;
}

std::vector<std::shared_ptr<Descriptor>> Model::get_identifier_of_granular_entity() const
{
    vector<std::shared_ptr<Descriptor>> shared_descriptor_vec;

    //select the entity.
    shared_ptr<Entity> e = get_entity(hash::EntityID("G"));

    // ask the entity for its identifying descriptors.
    if (e!=nullptr)
        shared_descriptor_vec=e->get_identifying_descriptor_set();

    return shared_descriptor_vec;
}

void Model::found_descriptor(sdg::hash::DescriptorInstance a_descriptor)
{
    std::shared_ptr<Entity> e = get_entity(hash::EntityID(a_descriptor.get_descriptor_id()));

    if(e && a_descriptor.get_descriptor_value() + 1 > e->get_count())
    {
        e->set_counter(a_descriptor.get_descriptor_value() + 1);
    }
}

int32_t Model::get_entity_count(sdg::hash::EntityID a_entity_id) const
{
    shared_ptr<Entity> e = this->get_entity(a_entity_id);


    return (e != nullptr)
    ? e->get_count()
    : 0;
}