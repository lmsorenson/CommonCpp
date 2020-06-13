// Copyright 2020 Lucas Sorenson, All rights reserved.
#include "../IndependentEntity.hpp"
#include <iostream>

using sdg::parse::IndependentEntity;
using std::string;
using std::cout;
using std::endl;

string IndependentEntity::get_id() const
{
    return string();
}

void IndependentEntity::new_node()
{
    count_up();
}