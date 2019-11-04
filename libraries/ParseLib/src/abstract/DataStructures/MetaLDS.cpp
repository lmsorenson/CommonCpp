// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "MetaLDS.hpp"
#include <iostream>


using namespace std;




void Model::add_thing(shared_ptr<Thing> a_thing)
{
    thing_array.push_back(a_thing);
}

shared_ptr<Entity> Model::get_entity(string a_entity_id_label)
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

vector<string> Model::get_entity_identifier(string a_entity_label)
{
    vector<string> str_vec;

    //select the entity.
    shared_ptr<Entity> e = get_entity(a_entity_label);

    //ask the entity for it's identifying descriptors.
    if (e!=nullptr)
        str_vec=e->get_identifying_descriptors();

    return str_vec;
}

void Model::increment_entity_counter(string a_entity_label)
{
    shared_ptr<Entity> e = get_entity(a_entity_label);
    
    e->increment_counter();
}

int32_t Model::get_entity_count(string a_entity_label)
{
    shared_ptr<Entity> e = get_entity(a_entity_label);
    
    return e->get_count();
}

Thing::Thing(string a_name)
: name(a_name)
, counter(0)
{
}

Thing::Thing(string a_name, string a_label)
: name(a_name)
, thing_id(a_label)
, counter(0)
{
}

void Thing::print()
{
    cout << this->name << endl;
}

string Thing::get_id()
{
    return thing_id;
}

void Thing::increment_counter()
{
    counter++;
}

int32_t Thing::get_count()
{
    return counter;
}


Identifier::Identifier(shared_ptr<Entity> a_owner)
: owning_entity(a_owner)
{
}

void Identifier::add_descriptor(shared_ptr<Descriptor> a_descriptor)
{
    this->descriptor_array.push_back(a_descriptor);
}

vector<string> Identifier::get_descriptor_labels()
{
    vector<string> result;
    for(int i=0; i<this->descriptor_array.size(); i++)
    {
        shared_ptr<Attribute> a;
        shared_ptr<Link> l;
        if((a=dynamic_pointer_cast<Attribute>(this->descriptor_array[i])))
            result.push_back(a->get_label());

        else if((l=dynamic_pointer_cast<Link>(this->descriptor_array[i])))
        {
            for( string label : l->get_labels())
            {
                result.push_back(label);
            }
        }
    }
    return result;
}


Entity::Entity(string a_entity_id, string a_name)
: Thing(a_name, a_entity_id )
{
}

//default param for identifier index is 0
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

vector<string> Entity::get_identifying_descriptors()
{
    vector<string> result;

    //todo-->support multiple identifiers
    if(!identifier_array.empty())//only populate result as per this proposition.
        result = this->identifier_array[0]->get_descriptor_labels();
    
    return result;
}

Relationship::Relationship(string a_name, shared_ptr<Entity> a_linked_entity, shared_ptr<Entity> a_linked_entity_2, bool a_be, IDENTIFY_BY ID_BY)
: Thing(a_name)
{
    a_linked_entity->add_descriptor(make_shared<Link>(Link("link_name", a_linked_entity_2, (a_be)?"be":"")), (ID_BY==LINK_1));
    a_linked_entity_2->add_descriptor(make_shared<Link>(Link("link_name", a_linked_entity, (a_be)?"be":"")), (ID_BY==LINK_2));
}

Descriptor::Descriptor(string a_name)
: Thing(a_name)
{
}

Link::Link(string a_name, shared_ptr<Entity> a_entity, string a_link_label)
: Descriptor(a_name)
, link_subject(a_entity)
, link_label(a_link_label)
{
}

vector<string> Link::get_labels()
{
    vector<string> r_descriptor_labels;
     //if the link subject is valid get descriptors identifying the linked entity.
    if (link_subject)
        r_descriptor_labels = link_subject->get_identifying_descriptors();

    return r_descriptor_labels;
}

Attribute::Attribute(string a_name, string a_label)
: Descriptor(a_name)
, attribute_label(a_label)
{
}

string Attribute::get_label()
{
    return attribute_label;
}