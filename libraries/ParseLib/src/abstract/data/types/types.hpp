// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once

#include "../meta/Descriptor.hpp"

namespace sdg {


namespace hash {

class DescriptorInstance;

class KeyInstance
{
public:
    explicit KeyInstance()=default;
    explicit KeyInstance(std::string a_value, bool a_is_partial_key=false);
    KeyInstance(std::vector<DescriptorInstance> descriptor, bool a_is_partial_key=false);

    bool is_partial_key() const;
    std::string as_string() const ;

private:
    std::string value_;
    bool is_partial_key_;
};


class DescriptorID
{
public:
    explicit DescriptorID()=default;
    explicit DescriptorID(std::string a_id);
    ~DescriptorID()=default;

    std::string as_string() const;

private:
    std::string id_;
};




class DescriptorInstance
{
public:
    explicit DescriptorInstance();
    explicit DescriptorInstance(std::string a_descriptor_id, Attribute::Scale a_attr_scale);

    int32_t get_descriptor_value() const;
    std::string get_descriptor_id() const;

    std::string as_string() const;
    
    Attribute::Scale get_scale() const;
    bool is_found() const;

    void set_value(int32_t a_value);
    void set_found();

    bool operator== (const char * &str)
    {
        std::string buffer;
        buffer.append(id_).append(std::to_string(value_));
        return (buffer.compare(std::string(str))==0);
    }

    bool operator== (const std::string &str)
    {
        std::string buffer;
        buffer.append(id_).append(std::to_string(value_));
        return (buffer.compare(str)==0);
    }

    DescriptorInstance &operator++( int n );

private:
    std::string id_;
    int32_t value_;
    Attribute::Scale attribute_scale_;
    bool b_is_found_;

};

class EntityID
{
public:
    explicit EntityID()=default;
    explicit EntityID(std::string a_id);
    ~EntityID()=default;

    std::string as_string() const;

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