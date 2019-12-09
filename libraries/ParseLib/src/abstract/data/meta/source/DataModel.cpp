// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <iostream>

#include "../DataModel.hpp"
#include "../Relationship.hpp"
#include "../Entity.hpp"


using namespace std;




void Model::add_thing(shared_ptr<Thing> a_thing)
{
    thing_array.push_back(a_thing);
}

shared_ptr<Entity> Model::get_entity(string a_entity_id_label) const
{
    shared_ptr<Entity> result;

    //get the entity.
    for(auto thing : this->thing_array)
    {
        shared_ptr<Entity> found_entity = nullptr;

        //thing is an entity and the label matches the argument label.
        if((found_entity=dynamic_pointer_cast<Entity>(thing)))
        {
            if (a_entity_id_label.compare(found_entity->get_id())==0)
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

vector<string> Model::get_entity_identifier(string a_entity_label) const
{
    vector<string> str_vec;

    //select the entity.
    shared_ptr<Entity> e = get_entity(a_entity_label);

    //ask the entity for it's identifying descriptors.
    if (e!=nullptr)
        str_vec=e->get_identifying_descriptor_id_set();

    return str_vec;
}

std::vector<std::shared_ptr<Descriptor>> Model::get_identifier_of_granular_entity() const
{
    vector<std::shared_ptr<Descriptor>> shared_descriptor_vec;

    //select the entity.
    shared_ptr<Entity> e = get_entity("G");

    // ask the entity for its identifying descriptors.
    if (e!=nullptr)
        shared_descriptor_vec=e->get_identifying_descriptor_set();

    return shared_descriptor_vec;
}

void Model::found_descriptor(std::string a_descriptor)
{
    char scanned_label[1];
    int32_t scanned_index;

    //scan the token
    sscanf(a_descriptor.c_str(), "%1s%i", scanned_label, &scanned_index);

    std::shared_ptr<Entity> e = get_entity(scanned_label);
    scanned_index++;

    if(scanned_index>e->get_count())
    {
        e->set_counter(scanned_index);
    }
}

int32_t Model::get_entity_count(string a_entity_label) const
{
    shared_ptr<Entity> e = this->get_entity(a_entity_label);
    
    return e->get_count();
}