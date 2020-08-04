// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../Relationship.hpp"
#include "../Entity.hpp"

using std::vector;
using std::string;
using std::make_shared;
using std::shared_ptr;



using sdg::Relationship;


Relationship::Relationship(const string &a_name, shared_ptr<Entity> a_linked_entity, shared_ptr<Entity> a_linked_entity_2, bool a_be, IDENTIFY_BY ID_BY)
: Thing(a_name)
{
    a_linked_entity->add_descriptor(make_shared<Link>(Link("link_name", a_linked_entity_2, (a_be)?"be":"")), (ID_BY==LINK_1));
    a_linked_entity_2->add_descriptor(make_shared<Link>(Link("link_name", a_linked_entity, (a_be)?"be":"")), (ID_BY==LINK_2));
}