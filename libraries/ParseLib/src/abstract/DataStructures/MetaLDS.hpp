// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once

#include <vector>
#include <string>


class Model;
class Thing;
class Identifier;

class Entity;
class Descriptor;
class Relationship;

class Attribute;
class Link;
class Degree;


class Model
{
    std::vector<std::shared_ptr<Thing>> thing_array;
};

class Thing
{
    std::string name;
};

class Identifier 
{
    std::shared_ptr<Entity> owning_entity;
    std::vector<std::shared_ptr<Descriptor>> descriptor_array; 
};


class Entity : public Thing
{
    std::vector<std::shared_ptr<Descriptor>> descriptor_array; 
    std::vector<std::shared_ptr<Identifier>> identifier_array; 
};

class Descriptor : public Thing
{
    std::shared_ptr<Entity> owning_entity;
    std::vector<std::shared_ptr<Identifier>> identifier_array; 
    std::shared_ptr<Degree> degree;
};

class Relationship : public Thing
{
    bool to_be_flag;

    std::vector<std::shared_ptr<Link>> link_array;
};

class Link : public Descriptor
{
    std::shared_ptr<Relationship> owning_relationship;
    std::shared_ptr<Degree> degree;

    std::string label;
};

class Attribute : public Identifier
{
    enum Scale
    {
        Numeric,
        Nominal,
        Ordinal,
        Boolean,
        NULL
    } scale;
};

class Degree
{
    int32_t datum;
};

