// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../Descriptor.hpp"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "../Entity.hpp"
#include "../Relationship.hpp"
#include "../../types/types.hpp"

using sdg::Entity;
using sdg::Descriptor;
using sdg::Attribute;
using sdg::Link;
using std::string;
using std::vector;
using std::string;
using sdg::hash::DescriptorID;




Descriptor::Descriptor(const string &a_name)
: Thing(a_name)
{
}

Descriptor::Descriptor(const string &a_name, const string &a_id)
: Thing(a_name, a_id)
{
}


Link::Link(const std::string &a_name, std::shared_ptr<Entity> a_entity, const string &a_link_label)
: Descriptor(a_name)
, link_subject_(a_entity)
, link_label_(a_link_label)
{
}

vector<DescriptorID> Link::get_identifying_descriptor_IDs()
{
    vector<DescriptorID> r_descriptor_labels;

     //if the link subject is valid get descriptors identifying the linked entity.
    if (link_subject_)
        r_descriptor_labels = link_subject_->get_identifying_descriptor_id_set();

    return r_descriptor_labels;
}

std::vector<std::shared_ptr<Descriptor>> Link::get_descriptors()
{
    using std::vector;
    using std::string;

    vector<std::shared_ptr<Descriptor>> r_descriptor_set;
     //if the link subject is valid get descriptors identifying the linked entity.
    if (link_subject_)
        r_descriptor_set = link_subject_->get_identifying_descriptor_set();

    return r_descriptor_set;
}


Attribute::Attribute(const string &a_name, const string &a_label, Attribute::Scale a_scale)
: Descriptor(a_name, a_label)
, attribute_label_(a_label)
, attr_scale_(a_scale)
{}

std::string Attribute::get_label() const
{
    return attribute_label_;
}

Attribute::Scale Attribute::get_scale() const
{
    return attr_scale_;
}