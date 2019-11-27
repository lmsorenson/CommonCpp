// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once

#include <vector>
#include <string>
#include <memory>

template <class T> using ManyLink = std::vector<std::shared_ptr<T>>;
template <class T> using OneLink = std::shared_ptr<T>;

#include "Interface.hpp"
#include "Entity.hpp"


class Model
{

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


private:
    ManyLink<Thing> thing_array;

    std::shared_ptr<Entity> get_entity(std::string a_entity_id_label);
};
