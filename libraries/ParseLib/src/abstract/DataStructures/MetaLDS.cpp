// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "MetaLDS.hpp"


using namespace std;




Thing::Thing(string a_name)
: name(a_name)
{
}

Entity::Entity(string name, shared_ptr<Identifier> a_identifier)
: Thing(name)
{
    identifier_array.push_back(a_identifier);
}

Entity::Entity(string name, vector<shared_ptr<Identifier>> a_identifier_set)
: Thing(name)
{
    for(auto id : a_identifier_set)
    {
        identifier_array.push_back(id);
    }
}

void Entity::add_descriptor(shared_ptr<Descriptor> a_descriptor)
{
    descriptor_array.push_back(a_descriptor);
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