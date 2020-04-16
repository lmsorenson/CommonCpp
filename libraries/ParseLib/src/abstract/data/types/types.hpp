// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once

#include "../meta/Descriptor.hpp"

namespace sdg {


namespace hash {

class DescriptorInstance;

class KeyInstance
{
public:
    KeyInstance() = default;
    KeyInstance(std::string a_value, bool a_is_partial_key=false);
    KeyInstance(std::vector<DescriptorInstance> descriptor, bool a_is_partial_key=false);

    bool is_partial_key();
    std::string value();

private:
    std::string value_;
    bool is_partial_key_;
};


class DescriptorID
{
public:
    DescriptorID()=default;
    DescriptorID(std::string a_id);
    ~DescriptorID()=default;

    std::string to_string();

private:
    std::string id_;
};




class DescriptorInstance
{
public:
    DescriptorInstance();
    DescriptorInstance(std::string a_descriptor_id, Attribute::Scale a_attr_scale);

    int32_t get_descriptor_value() const;
    std::string get_descriptor_id() const;
    Attribute::Scale get_scale() const;
    bool is_found() const;

    void set_value(int32_t a_value);
    void set_found();

private:
    std::string id_;
    int32_t value_;
    Attribute::Scale attribute_scale_;
    bool b_is_found_;

};

class EntityID
{
public:
    EntityID()=default;
    EntityID(std::string a_id);
    ~EntityID()=default;

    std::string to_string();

    bool operator== (const char * &str)
    {
        return (id_.compare(std::string(str))==0);
    }

    bool operator== (const std::string &str)
    {
        return (id_.compare(str)==0);
    }

private:
    std::string id_;
};

}//namespace hash
}//namespace sdg