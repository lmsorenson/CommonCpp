// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <memory>
#include <vector>
#include <string>




namespace sdg
{

template <class T> using ManyLink = std::vector<std::shared_ptr<T>>;
template <class T> using OneLink = std::shared_ptr<T>;

class Thing
{
public:
    Thing(const std::string &a_name);
    Thing(const std::string &a_name, const std::string &a_label);
    virtual ~Thing()=default;

    virtual void print();
    std::string get_id() const;

    void set_counter(int32_t a_value);
    int32_t get_count() const;

private:
    std::string name_;
    std::string thing_id_;
    int32_t counter_;
};

}// namespace sdg