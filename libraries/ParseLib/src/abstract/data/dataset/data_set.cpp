// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <objects/data_set.hpp>
#include <iostream>





//-- Constructors ----------------------------------
sdg::DataSet::DataSet()
: state(DATA_SET_EMPTY) {}

sdg::DataSet::DataSet(State a_state)
: state(a_state) {}

sdg::DataSet::DataSet(int32_t hash_table_size)
: hash_table(hash_table_size)
, state(DATA_SET_GOOD) {}



//-- Deconstructors --------------------------------
sdg::DataSet::~DataSet(){}



//-- Operators -------------------------------------
sdg::Instance sdg::DataSet::operator[](std::string i)
{
    return this->get(i);
}
