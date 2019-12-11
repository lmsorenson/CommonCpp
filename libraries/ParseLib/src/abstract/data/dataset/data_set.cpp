// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <objects/data_set.hpp>
#include <iostream>

#include <ParseLib.hpp>





//-- Constructors ----------------------------------
sdg::DataSet::DataSet()
: state(DATA_SET_EMPTY) {}

sdg::DataSet::DataSet(State a_state)
: state(a_state) {}

sdg::DataSet::DataSet(int32_t hash_table_size)
: hash_table_(hash_table_size)
, state(DATA_SET_GOOD) {}



//-- Deconstructors --------------------------------
sdg::DataSet::~DataSet(){}



//-- Operators -------------------------------------
sdg::Instance sdg::DataSet::operator[](std::string i)
{
    return this->get(i);
}



sdg::DataSet sdg::DataSet::Read(std::string a_path, int32_t * status_code)
{
    int32_t return_code;
    return_code = ParseLib().read_file(*this, a_path.c_str());
    if(status_code!=nullptr)
        *status_code = return_code;

    return *this;
}

sdg::DataSet sdg::DataSet::Read(std::string a_path, std::vector<option> read_options, int32_t * status_code)
{
    int32_t return_code;
    return_code = ParseLib().read_file(*this, a_path.c_str(), read_options);
    if(status_code!=nullptr)
        *status_code = return_code;

    return *this;
}

void sdg::DataSet::Write(std::string a_path, int32_t * status_code)
{
    int32_t return_code;
    return_code = ParseLib().write_file(*this, a_path.c_str());
    if(status_code!=nullptr)
        *status_code = return_code;

}

void sdg::DataSet::Write(std::string a_path, std::vector<option> write_options, int32_t * status_code)
{
    int32_t return_code;
    return_code = ParseLib().write_file(*this, a_path.c_str(), write_options);
    if(status_code!=nullptr)
        *status_code = return_code;
}