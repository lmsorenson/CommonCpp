// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "../types.hpp"
#include "../../meta/Descriptor.hpp"


using ::sdg::hash::KeyInstance;
using ::sdg::hash::DescriptorID;
using ::sdg::hash::DescriptorInstance;
using ::sdg::hash::EntityID;
using ::std::string;


KeyInstance::KeyInstance(const string& a_value, bool a_is_partial_key)
: value_(a_value)
, is_partial_key_(a_is_partial_key)
{}


KeyInstance::KeyInstance(std::vector<DescriptorInstance> descriptors, bool a_is_partial_key)
: is_partial_key_(a_is_partial_key)
{
    for(int i=0; i<descriptors.size(); i++)
    {
        if(i>0)
            value_.append("-");

        value_.append(descriptors[i].get_descriptor_id());
        value_.append(std::to_string(descriptors[i].get_descriptor_value()));
    }
}

bool KeyInstance::is_default() const
{
    return (value_.empty() && is_partial_key_ == false);
}

bool KeyInstance::is_partial_key() const
{
    return is_partial_key_;
}


string KeyInstance::as_string() const
{
    return value_;
}

void KeyInstance::for_each_descriptor(std::function<void(const string&)> callback)
{
    char * token = strtok((char*)value_.c_str(),"-");

    //iterates through all tokens(descriptors)
    while(token!=NULL)
    {
        callback(string(token));

        token = strtok(NULL,"-");
    }

    delete[] token;
}


DescriptorID::DescriptorID(const string& a_id)
: id_(a_id)
{

}

string DescriptorID::as_string() const
{
    return id_;
}


DescriptorInstance::DescriptorInstance()
: id_("")
, value_(-1)
, attribute_scale_(Attribute::Scale::Unknown)
, b_is_found_(false)
{}

DescriptorInstance::DescriptorInstance( const string& a_descriptor_id, Attribute::Scale a_attr_scale)
: id_(a_descriptor_id)
, value_(-1)
, attribute_scale_(a_attr_scale)
, b_is_found_(false)
{}


DescriptorInstance& DescriptorInstance::operator++( int n )
{
    if( n != 0 )
        value_ += n;
    else
        value_++;

    return *this;
}

bool DescriptorID::operator==(const DescriptorID& rhs) const
{
    return (this->id_.compare(rhs.id_) == 0);
}


int32_t DescriptorInstance::get_descriptor_value() const
{
    return value_;
}


string DescriptorInstance::get_descriptor_id() const
{
    return id_;
}


string DescriptorInstance::as_string() const
{
    string return_variable;
    return return_variable.append(id_).append(std::to_string(value_));
}


sdg::Attribute::Scale DescriptorInstance::get_scale() const
{
    return attribute_scale_;
}


bool DescriptorInstance::is_found() const
{
    return b_is_found_;
}


void DescriptorInstance::set_value(int32_t a_value)
{
    value_=a_value;
}


void DescriptorInstance::set_found()
{
    b_is_found_=true;
}

EntityID::EntityID(const string& a_id)
: id_(a_id)
{

}

string EntityID::as_string() const
{
    return id_;
}
