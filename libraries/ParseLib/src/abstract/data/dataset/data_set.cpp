// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <objects/data_set.hpp>
#include <iostream>

#include <ParseLib.hpp>




//-- Constructors ----------------------------------
/**
 * A constructor for a dataset.  Creates an empty dataset.
 */
sdg::DataSet::DataSet()
: state_(DATA_SET_EMPTY)
, hash_table_(100)
{}

/**
 * A constructor for a dataset.  Creates a dataset with a specific initial state.
 * @param a_state The initial state of the dataset.
 */
sdg::DataSet::DataSet(State a_state)
: state_(a_state)
, hash_table_(1)
{}

/**
 * A constructor for a dataset.  Creates an empty dataset with a specific hash table size.
 * @param hash_table_size The size of the hash table.
 */
sdg::DataSet::DataSet(int32_t hash_table_size)
: hash_table_(hash_table_size)
, state_(DATA_SET_EMPTY)
{}



//-- Destructors --------------------------------
/**
 * A destructor
 */
sdg::DataSet::~DataSet(){}



//-- Operators -------------------------------------
/**
 * An overload of the index operator that takes a string id as a parameter.
 * @param i The id of the key instance.
 * @return A dataset instance.
 */
sdg::Instance sdg::DataSet::operator[](std::string i)
{
    return this->get(hash::KeyInstance(i));
}


/**
 * Reads a dataset from a file.
 * @param a_path The path to the file.
 * @param status_code A code which indicates the level of success or failure of the operation.
 * @return A dataset.
 */
sdg::DataSet sdg::DataSet::Read(std::string a_path, int32_t * status_code)
{
    int32_t return_code;
    return_code = ParseLib().read_file(*this, a_path.c_str());
    if(status_code!=nullptr)
        *status_code = return_code;

    return *this;
}

/**
 * Reads this dataset from a file.
 * @param a_path The path to the file.
 * @param read_options Options for the read operation.
 * @param status_code A code which indicates the level of success or failure of the operation.
 * @return A dataset.
 */
sdg::DataSet sdg::DataSet::Read(std::string a_path, std::vector<sdg::option> read_options, int32_t * status_code)
{
    int32_t return_code;
    return_code = ParseLib().read_file(*this, a_path.c_str(), read_options);
    if(status_code!=nullptr)
        *status_code = return_code;

    return *this;
}

/**
 * Writes this dataset to a file.
 * @param a_path The path to the output file.
 * @param status_code A code which indicates the level of success or failure of the operation.
 */
void sdg::DataSet::Write(std::string a_path, int32_t * status_code)
{
    int32_t return_code = 0;
    return_code = ParseLib().write_file(*this, a_path.c_str());
    if(status_code!=nullptr)
        *status_code = return_code;
}

/**
 * Writes this dataset to a file.
 * @param a_path The path to the output file.
 * @param write_options Options for the write operation.
 * @param status_code A code which indicates the level of success or failure of the operation.
 */
void sdg::DataSet::Write(std::string a_path, std::vector<option> write_options, int32_t * status_code)
{
    int32_t return_code;
    return_code = ParseLib().write_file(*this, a_path.c_str(), write_options);
    if(status_code!=nullptr)
        *status_code = return_code;
}