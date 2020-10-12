// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../Entity.hpp"
#include "../Descriptor.hpp"
#include "../../types/types.hpp"
#include <iostream>

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::string;

using ::sdg::Entity;
using ::sdg::Descriptor;
using ::sdg::Identifier;
using ::std::vector;
using ::std::cout;
using ::std::endl;

/**
 * The constructor for an Entity.
 * @param a_entity_id A unique identifier for an entity.  Within a model no two entities can contain have the same entity id.
 * @param a_name A name for the thing.
 */
Entity::Entity(const string &a_entity_id, const string &a_name)
: Thing(a_name, a_entity_id )
, identifier_array_(0, nullptr )
, descriptor_array_(0, nullptr )
{
    auto id = make_shared<Identifier>(Identifier(this));
    identifier_array_.push_back(id);
}

/**
 * Add a single descriptor to the entity.
 * @param a_descriptor The descriptor to add.
 * @param b_is_identifying_descriptor Indicates whether or not the current descriptor is an identifying descriptor.
 * @param identifier_index The identifier to add the descriptor to.
 */
void Entity::add_descriptor(shared_ptr<Descriptor> a_descriptor, bool b_is_identifying_descriptor, int32_t identifier_index)
{
    descriptor_array_.push_back(a_descriptor);

    if(b_is_identifying_descriptor)
    {
        //todo -- something could go wrong if the supplied index greater than size+1 
        if(!identifier_array_.empty() && (identifier_array_.size()-1) >= identifier_index)
        {
            identifier_array_[identifier_index]->add_descriptor(a_descriptor);
        }
        else
        {
            cout << "The identifier index was out of range." << endl;
        }
    }
}

/**
 *
 * @return
 */
vector<sdg::hash::DescriptorID> Entity::get_identifying_descriptor_id_set()
{
    vector<hash::DescriptorID> result;

    //todo-->support multiple identifiers
    if(!identifier_array_.empty())//only populate result as per this proposition.
        result = this->identifier_array_[0]->get_descriptor_ids();
    
    return result;
}


/**
 *
 * @return
 */
vector<shared_ptr<Descriptor>> Entity::get_identifying_descriptor_set()
{
    vector<shared_ptr<Descriptor>> result;

    //todo-->support multiple identifiers
    if(!identifier_array_.empty())//only populate result as per this proposition.
        result = this->identifier_array_[0]->get_descriptors();
    
    return result;
}

/**
 * Number of descriptors.
 * @return The total number of descriptors associated with this entity.
 */
size_t Entity::num_descriptors() const
{
    return descriptor_array_.size();
}

/**
 * Gets the size of the target identifier.
 * @param a_identifier_index The target identifier.
 * @return The size of the target identifier.  Returns 0 if the target identifier doesn't exist.
 */
size_t Entity::num_identifying_descriptors(int32_t a_identifier_index) const
{
    if (identifier_array_[a_identifier_index] != nullptr)
        return identifier_array_[a_identifier_index]->num_descriptors();

    else
        return 0;
}



/**
 * A constructor for an Identifier.
 * @param a_owner A pointer to the owner of this identifier.
 */
Identifier::Identifier(Entity * a_owner)
: owning_entity_(a_owner)
{
}

/**
 * Add a descriptor reference to the identifier.
 * @param a_descriptor A descriptor pointer to add.
 */
void Identifier::add_descriptor(shared_ptr<Descriptor> a_descriptor)
{
    this->descriptor_array_.push_back(a_descriptor);
}


/**
 * Gets a list of descriptor ids.
 * @return A vector of descriptor ids.
 */
vector<sdg::hash::DescriptorID> Identifier::get_descriptor_ids()
{
    vector<hash::DescriptorID> result;
    for(int i=0; i<this->descriptor_array_.size(); i++)
    {
        shared_ptr<Attribute> a;
        shared_ptr<Link> l;
        if((a=dynamic_pointer_cast<Attribute>(this->descriptor_array_[i])))
        {
            result.push_back(hash::DescriptorID(a->get_label()));
        }

        else if((l=dynamic_pointer_cast<Link>(this->descriptor_array_[i])))
        {
            for( hash::DescriptorID ID : l->get_identifying_descriptor_IDs())
            {
                result.push_back(ID);
            }
        }
    }
    return result;
}

/**
 * Get a list of descriptors associated with this identifier.
 * @return A vector of descriptors associated with this identifier.
 */
vector<std::shared_ptr<Descriptor>> Identifier::get_descriptors()
{
    vector<std::shared_ptr<Descriptor>> result;
    for(int i=0; i<this->descriptor_array_.size(); i++)
    {
        shared_ptr<Attribute> a;
        shared_ptr<Link> l;
        if((a=dynamic_pointer_cast<Attribute>(this->descriptor_array_[i])))
            result.push_back(a);

        else if((l=dynamic_pointer_cast<Link>(this->descriptor_array_[i])))
        {
            for( auto descriptor : l->get_identifying_descriptors())
            {
                result.push_back(descriptor);
            }
        }
    }
    return result;
}

/**
 * Get the number of descriptors associated with this identifier.
 * @return The size of the descriptor array.
 */
size_t Identifier::num_descriptors() const
{
    return descriptor_array_.size();
}