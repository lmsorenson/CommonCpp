// Copyright 2019, Lucas Sorenson, All rights reserved
#include "../Interface.hpp"
#include <iostream>

#include "../Entity.hpp"
#include "../Relationship.hpp"



using sdg::Thing;
using std::string;



Thing::Thing(const string &a_name)
: name(a_name)
, counter(0)
{
}

Thing::Thing(const string &a_name, const string &a_label)
: name(a_name)
, thing_id(a_label)
, counter(0)
{
}

void Thing::set_counter(int32_t a_value)
{
    counter = a_value;
}

void Thing::print()
{
    std::cout << this->name << std::endl;
}

std::string Thing::get_id() const
{
    return thing_id;
}

int32_t Thing::get_count() const
{
    return counter;
}




