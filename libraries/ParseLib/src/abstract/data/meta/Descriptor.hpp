// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once

#include "Interface.hpp"

class Entity;
class Relationship;
class Identifier;

class Degree
{
    int32_t datum;
};

class Descriptor : public Thing
{

public:
    Descriptor(std::string a_name);
    Descriptor(std::string a_name, std::string a_id);
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
    Link(std::string a_name, std::shared_ptr<Entity> a_entity, std::string a_link_label="");
    ~Link()=default;

    std::vector<std::string> get_descriptor_IDs();
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

    Attribute(std::string a_name, std::string a_label, Scale a_scale);
    ~Attribute()=default;

    bool IsRequired();

    std::string get_label() const;
    Scale get_scale() const;

private:
    
    Scale attr_scale;

    std::string attribute_label;
};