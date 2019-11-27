// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <memory>
#include <vector>
#include <string>

template <class T> using ManyLink = std::vector<std::shared_ptr<T>>;
template <class T> using OneLink = std::shared_ptr<T>;

class Thing
{

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

private:
    std::string name;
    std::string thing_id;

    int32_t counter; 

};
