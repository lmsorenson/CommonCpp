// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../Descriptor.hpp"
#include <string>
#include <vector>
#include <memory>

#include "../Entity.hpp"
#include "../Relationship.hpp"

Descriptor::Descriptor(std::string a_name)
: Thing(a_name)
{
}


Link::Link(std::string a_name, std::shared_ptr<Entity> a_entity, std::string a_link_label)
: Descriptor(a_name)
, link_subject(a_entity)
, link_label(a_link_label)
{
}

std::vector<std::string> Link::get_labels()
{
    using std::vector;
    using std::string;

    vector<string> r_descriptor_labels;
     //if the link subject is valid get descriptors identifying the linked entity.
    if (link_subject)
        r_descriptor_labels = link_subject->get_identifying_descriptors();

    return r_descriptor_labels;
}


Attribute::Attribute(std::string a_name, std::string a_label)
: Descriptor(a_name)
, attribute_label(a_label)
{
}

std::string Attribute::get_label()
{
    return attribute_label;
}