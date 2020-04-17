// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>

#include "../src/abstract/data/types/types.hpp"



namespace sdg {

class DataSet;

class Instance
{
public:
    enum State : int32_t
    {
        VALID_INST,
        NULL_INST,
        NO_FILE,
        UNKNOWN
    };

    Instance() = default;
    Instance(const sdg::DataSet * owner, State a_state);
    Instance(const sdg::DataSet * owner, State a_state, std::string a_key);
    ~Instance();

    Instance operator[](std::string i);

    // Instance Public API 
    //-- Accessors
    std::string get() const;                                    //only returns a value if a vector has a particular value
    std::vector<std::string> get_vector();
    std::string at(int8_t a_index) const;                       //get a specific value within the value list.
    const std::vector<std::string>::iterator begin();           //returns an iterator to the beginning of the value list.
    const std::vector<std::string>::iterator end();             //returns an iterator at the end of the value list.

    Instance GetNextInstance(hash::DescriptorID a_descriptor_id) const;      //next value in a set of instances.
    Instance GetPreviousInstance(hash::DescriptorID a_descriptor_id) const;  //previous value in a set of instances.
    Instance GetRelatedInstance(hash::DescriptorID a_descriptor_id) const;        //returns a related entity.
    
    bool is_valid() const;                                      //tells us if the instance is valid.
    int32_t FindIndexOfValue(std::string a_value_to_search_for, int32_t offset=0) const;    //finds the index of a certain value within the instance if it exists.


    //-- Mutators --
    void add_value(std::string str_value);      //add a value
    void set_key(std::string a_key);            //assign the key


private:
    //instance meta data
    const sdg::DataSet * kOwner_;           //<-- the DataSet of origin.
    State state_;                           //<-- the State of the instance.
    std::string key_;                       //<-- the key used to get this instance.

    //instance data
    std::vector<std::string> value_;        //<-- the values stored.
    
    //gets the descriptor for an entity containing this entity instance.
    //used to get references to related instances.
    //*** takes in a descriptor id, returns a descriptor with a value, or if null "NO_VALUE" ***
    std::string GetDescriptorByDescriptorID(hash::DescriptorID a_descriptor_id) const;
};

}//namespace sdg