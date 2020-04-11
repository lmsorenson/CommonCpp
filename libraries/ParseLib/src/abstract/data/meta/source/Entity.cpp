// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../Entity.hpp"
#include "../Descriptor.hpp"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::string;


using sdg::Entity;
using sdg::Descriptor;
using sdg::Identifier;

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

vector<string> Entity::get_identifying_descriptor_id_set()
{
    vector<string> result;

    //todo-->support multiple identifiers
    if(!identifier_array.empty())//only populate result as per this proposition.
        result = this->identifier_array[0]->get_descriptor_ids();
    
    return result;
}


vector<shared_ptr<Descriptor>> Entity::get_identifying_descriptor_set()
{
    vector<shared_ptr<Descriptor>> result;

    //todo-->support multiple identifiers
    if(!identifier_array.empty())//only populate result as per this proposition.
        result = this->identifier_array[0]->get_descriptors();
    
    return result;
}




Identifier::Identifier(shared_ptr<Entity> a_owner)
: owning_entity(a_owner)
{
}

void Identifier::add_descriptor(shared_ptr<Descriptor> a_descriptor)
{
    this->descriptor_array.push_back(a_descriptor);
}

vector<string> Identifier::get_descriptor_ids()
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
            for( string ID : l->get_descriptor_IDs())
            {
                result.push_back(ID);
            }
        }
    }
    return result;
}

vector<std::shared_ptr<Descriptor>> Identifier::get_descriptors()
{
    vector<std::shared_ptr<Descriptor>> result;
    for(int i=0; i<this->descriptor_array.size(); i++)
    {
        shared_ptr<Attribute> a;
        shared_ptr<Link> l;
        if((a=dynamic_pointer_cast<Attribute>(this->descriptor_array[i])))
            result.push_back(a);

        else if((l=dynamic_pointer_cast<Link>(this->descriptor_array[i])))
        {
            for( auto descriptor : l->get_descriptors())
            {
                result.push_back(descriptor);
            }
        }
    }
    return result;
}