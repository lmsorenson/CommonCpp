// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once

#include "Interface.hpp"



namespace sdg {
    
namespace hash {

class DescriptorID;

}// namespace hash

class Entity;
class Relationship;
class Identifier;

class Degree
{
public:
    Degree():datum_(0){}

private:
    int32_t datum_;
};

class Descriptor : public Thing
{
public:
    explicit Descriptor(const std::string &a_name);
    explicit Descriptor(const std::string &a_name, const std::string &a_id);
    ~Descriptor()=default;

private:
    OneLink<Entity> owning_entity_;
    ManyLink<Identifier> identifier_array_;
    OneLink<Degree> degree_;
};


class Link : public Descriptor
{
    OneLink<Relationship> owning_relationship_;
    OneLink<Degree> degree_;

    std::string link_label_;
    OneLink<Entity> link_subject_;

public:
    explicit Link(const std::string &a_name, std::shared_ptr<Entity> a_entity, const std::string &a_link_label="");
    ~Link()=default;

    std::vector<hash::DescriptorID> get_identifying_descriptor_IDs();
    std::vector<std::shared_ptr<Descriptor>> get_descriptors();
};



class Attribute : public Descriptor
{

public:
    enum Scale
    {
        Numeric,
        Nominal,
        Ordinal,
        Boolean,
        Unknown
    };

    explicit Attribute(const std::string &a_name, const std::string &a_label, Scale a_scale);
    ~Attribute()=default;

    bool IsRequired();

    std::string get_label() const;
    Scale get_scale() const;

private:
    
    Scale attr_scale_;

    std::string attribute_label_;
};

}// namespace sdg