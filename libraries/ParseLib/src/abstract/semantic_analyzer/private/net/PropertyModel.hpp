// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>

namespace sdg {

class PropertySetBase
{
public:
    PropertySetBase() = default;
    virtual ~PropertySetBase() = default;

    virtual bool token_has_value()
    {

    }

private:

    std::string value_;// the value on the node.
};

class NodeProperties : public PropertySetBase
{
public:
    NodeProperties() = default;
    virtual ~NodeProperties() = default;

    bool child_of_root_node()
    {

    }
    std::string get_label()
    {

    }

private:
    std::string parent_value_;// the value on the parent.
    std::string child_num_;// the number of children on the node.
};

class RecordProperties : public PropertySetBase
{
public:
    RecordProperties() = default;
    virtual ~RecordProperties() = default;

private:
    int32_t set_position_;
    int32_t value_num_;
};

}// namespace sdg