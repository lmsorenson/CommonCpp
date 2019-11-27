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

    std::vector<std::string> get_labels();
};



class Attribute : public Descriptor
{

public:
    Attribute(std::string a_name, std::string a_label);
    ~Attribute()=default;

    std::string get_label();

private:
    enum Scale
    {
        Numeric,
        Nominal,
        Ordinal,
        Boolean,
        Unknown
    } 
    scale;

    std::string attribute_label;
};