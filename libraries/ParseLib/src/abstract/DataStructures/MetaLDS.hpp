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

template <class T> using ManyLink = std::vector<std::shared_ptr<T>>;
template <class T> using OneLink = std::shared_ptr<T>;


class Model
{
    ManyLink<Thing> thing_array;

public:
    Model()=default;
    ~Model()=default;
};

class Thing
{
    std::string name;

public:
    Thing(std::string a_name);
    ~Thing()=default;
};

class Identifier 
{
    OneLink<Entity> owning_entity;
    ManyLink<Descriptor> descriptor_array; 

public:
};


class Entity : public Thing
{
    ManyLink<Descriptor> descriptor_array; 
    ManyLink<Identifier> identifier_array; 

public:
    Entity(std::string name, std::shared_ptr<Identifier> a_identifier);
    Entity(std::string name, std::vector<std::shared_ptr<Identifier>> a_identifier_set);
    ~Entity()=default;

    void add_descriptor(std::shared_ptr<Descriptor> a_descriptor);
};

class Descriptor : public Thing
{
    OneLink<Entity> owning_entity;
    ManyLink<Identifier> identifier_array; 
    OneLink<Degree> degree;

public:
    Descriptor(std::string a_name);
    ~Descriptor()=default;
};

class Relationship : public Thing
{
    bool to_be_flag;
    ManyLink<Link> link_array;

public:
    Relationship(std::string a_name, std::shared_ptr<Entity> a_linked_entity, std::shared_ptr<Entity> a_linked_entity_2);
    ~Relationship()=default;
};

class Link : public Descriptor
{
    OneLink<Relationship> owning_relationship;
    OneLink<Degree> degree;

    std::string label;
    OneLink<Entity> link_subject;

public:
    Link(std::string a_name, std::shared_ptr<Entity> a_entity);
    ~Link()=default;
};

class Attribute : public Descriptor
{
    enum Scale
    {
        Numeric,
        Nominal,
        Ordinal,
        Boolean,
        Unknown
    } 
    scale;
};

class Degree
{
    int32_t datum;
};

