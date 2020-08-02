// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once

#include "Interface.hpp"



namespace sdg {
    
namespace hash {

class DescriptorID;

}// namespace hash

class Entity;
class Relationship;
class Identifier;

class Degree
{
public:
    Degree():datum_(0){}

private:
    int32_t datum_;
};

class Descriptor : public Thing
{

public:
    Descriptor(const std::string &a_name);
    Descriptor(const std::string &a_name, const std::string &a_id);
    ~Descriptor()=default;

private:
    OneLink<Entity> owning_entity;
    ManyLink<Identifier> identifier_array; 
    OneLink<Degree> degree;
};


class Link : public Descriptor
{
    OneLink<Relationship> owning_relationship;
    OneLink<Degree> degree;

    std::string link_label;
    OneLink<Entity> link_subject;

public:
    Link(const std::string &a_name, std::shared_ptr<Entity> a_entity, const std::string &a_link_label="");
    ~Link()=default;

    std::vector<hash::DescriptorID> get_descriptor_IDs();
    std::vector<std::shared_ptr<Descriptor>> get_descriptors();
};



class Attribute : public Descriptor
{

public:
    enum Scale
    {
        Numeric,
        Nominal,
        Ordinal,
        Boolean,
        Unknown
    } ;

    Attribute(const std::string &a_name, const std::string &a_label, Scale a_scale);
    ~Attribute()=default;

    bool IsRequired();

    std::string get_label() const;
    Scale get_scale() const;

private:
    
    Scale attr_scale;

    std::string attribute_label;
};

}// namespace sdg