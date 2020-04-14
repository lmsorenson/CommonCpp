// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../Descriptor.hpp"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "../Entity.hpp"
#include "../Relationship.hpp"
#include "../../keys/keys.hpp"

using sdg::Entity;
using sdg::Descriptor;
using sdg::Attribute;
using sdg::Link;




Descriptor::Descriptor(std::string a_name)
: Thing(a_name)
{
}

Descriptor::Descriptor(std::string a_name, std::string a_id)
: Thing(a_name, a_id)
{
}


Link::Link(std::string a_name, std::shared_ptr<Entity> a_entity, std::string a_link_label)
: Descriptor(a_name)
, link_subject(a_entity)
, link_label(a_link_label)
{
}

std::vector<sdg::hash::DescriptorID> Link::get_descriptor_IDs()
{
    using std::vector;
    using std::string;

    vector<hash::DescriptorID> r_descriptor_labels;

     //if the link subject is valid get descriptors identifying the linked entity.
    if (link_subject)
        r_descriptor_labels = link_subject->get_identifying_descriptor_id_set();

    return r_descriptor_labels;
}

std::vector<std::shared_ptr<Descriptor>> Link::get_descriptors()
{
    using std::vector;
    using std::string;

    vector<std::shared_ptr<Descriptor>> r_descriptor_set;
     //if the link subject is valid get descriptors identifying the linked entity.
    if (link_subject)
        r_descriptor_set = link_subject->get_identifying_descriptor_set();

    return r_descriptor_set;
}


Attribute::Attribute(std::string a_name, std::string a_label, Attribute::Scale a_scale)
: Descriptor(a_name, a_label)
, attribute_label(a_label)
, attr_scale(a_scale)
{}

std::string Attribute::get_label() const
{
    return attribute_label;
}

Attribute::Scale Attribute::get_scale() const
{
    return attr_scale;
}