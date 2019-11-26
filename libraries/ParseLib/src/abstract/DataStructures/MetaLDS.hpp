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

    std::shared_ptr<Entity> get_entity(std::string a_entity_id_label);

public:
    Model()=default;
    ~Model()=default;

    //add a thing to the data model.
    void add_thing(std::shared_ptr<Thing> a_thing);

    //get identifying descriptors for the entity specified
    std::vector<std::string> get_entity_identifier(std::string a_entity_label);

    //increment the counter for the entity specified
    void increment_entity_counter(std::string a_entity_label);
    void found_descriptor(std::string a_descriptor);

    int32_t get_entity_count(std::string a_entity_label);
};

class Thing
{
    std::string name;
    std::string thing_id;

    int32_t counter; 

public:
    Thing(std::string a_name);
    Thing(std::string a_name, std::string a_label);
    ~Thing()=default;

    virtual void print();
    std::string get_id();

    //pass in a descriptor to update the count
    void increment_counter();

    void set_counter(int32_t a_value);
    
    int32_t get_count();
};

class Identifier 
{
    OneLink<Entity> owning_entity;
    ManyLink<Descriptor> descriptor_array; 

public:
    Identifier(std::shared_ptr<Entity> a_owner);
    ~Identifier()=default;
    void add_descriptor(std::shared_ptr<Descriptor> a_descriptor);
    std::vector<std::string> get_descriptor_labels();
};


class Entity : public Thing
{
    ManyLink<Descriptor> descriptor_array; 
    ManyLink<Identifier> identifier_array; 

public:
    Entity(std::string a_entity_id, std::string a_name);
    ~Entity()=default;

    void add_descriptor(std::shared_ptr<Descriptor> a_descriptor, bool b_is_identifying_descriptor = false, int32_t identifier_index = 0);
    std::vector<std::string> get_identifying_descriptors();
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
    enum IDENTIFY_BY : int8_t
    {
        NO_ID,
        LINK_1,
        LINK_2
    };

    Relationship(std::string a_name, std::shared_ptr<Entity> a_linked_entity, std::shared_ptr<Entity> a_linked_entity_2, bool a_be = false, IDENTIFY_BY ID_BY = NO_ID);
    ~Relationship()=default;
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

public:
    Attribute(std::string a_name, std::string a_label);
    ~Attribute()=default;

    std::string get_label();
};

class Degree
{
    int32_t datum;
};

