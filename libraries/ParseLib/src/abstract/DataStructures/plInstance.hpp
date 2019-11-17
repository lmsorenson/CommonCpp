// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>




class plDataSet;

class plInstance
{
public:
    enum State : int32_t
    {
        VALID_INST,
        NULL_INST,
        NO_FILE,
        UNKNOWN
    };

private:
    const plDataSet * owning_data_set;
    std::string key;//the key that identifies this instance
    std::vector<std::string> value;//the values stored.
    State state;
    //gets the descriptor for an entity containing this entity instance.
    std::string get_descriptor(std::string a_label) const;

public:
    plInstance() = default;
    plInstance(const plDataSet * owner, State s);
    ~plInstance();

    std::string get() const;                                    //only returns a value if a vector has a particular value
    std::vector<std::string> get_vector();
    std::string at(int8_t index) const;                         //get a specific value within a list of 
    const std::vector<std::string>::iterator begin();
    const std::vector<std::string>::iterator end();
    plInstance pull_next(std::string a_label) const;            //next value in a set of instances.
    plInstance pull_previous(std::string a_label) const;        //previous value in a set of instances.
    plInstance related(std::string a_label) const;              //returns a related entity.
    bool is_valid() const;                                      //tells us if the instance is valid.
    int32_t find(std::string value, int32_t offset=0) const;

    void add(std::string str_value);//add a value
    void SetKey(std::string a_key);//assign the key
};