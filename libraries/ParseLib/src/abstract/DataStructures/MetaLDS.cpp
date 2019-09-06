// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "MetaLDS.hpp"


using namespace std;




void Model::add_thing(std::shared_ptr<Thing> a_thing)
{
    thing_array.push_back(a_thing);
}

Thing::Thing(string a_name)
: name(a_name)
{
}

Identifier::Identifier(std::shared_ptr<Entity> a_owner)
: owning_entity(a_owner)
{
}

void Identifier::add_descriptor(shared_ptr<Descriptor> a_descriptor)
{

}

Entity::Entity(string name)
: Thing(name)
{
}

void Entity::add_descriptor(shared_ptr<Descriptor> a_descriptor, bool b_is_identifying_descriptor, int32_t identifier_index)
{
    descriptor_array.push_back(a_descriptor);

    if(b_is_identifying_descriptor)
    {
        //todo -- something could go wrong if the supplied index greater than size+1 
        if(!identifier_array.empty() && (identifier_array.size()-1) >= identifier_index)
            identifier_array[identifier_index]->add_descriptor(a_descriptor);
        else
        {
            auto id = make_shared<Identifier>(Identifier(shared_ptr<Entity>(this)));
            id->add_descriptor(a_descriptor);
            identifier_array.push_back(id);
        }
    }
}

Relationship::Relationship(string a_name, shared_ptr<Entity> a_linked_entity, shared_ptr<Entity> a_linked_entity_2)
: Thing(a_name)
{
    a_linked_entity->add_descriptor(make_shared<Link>(Link("link_name", a_linked_entity_2)));
    a_linked_entity_2->add_descriptor(make_shared<Link>(Link("link_name", a_linked_entity)));
}

Descriptor::Descriptor(string a_name)
: Thing(a_name)
{
}

Link::Link(string a_name, shared_ptr<Entity> a_entity)
: link_subject(a_entity)
, Descriptor(a_name)
{
}

Attribute::Attribute(std::string a_name)
: Descriptor(a_name)
{
}