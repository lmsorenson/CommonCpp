// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <regex>

namespace sdg {

class PropertySetBase
{
public:
    PropertySetBase(std::string value)
    : value_(value)
    {}
    virtual ~PropertySetBase() = default;

    virtual bool token_has_value() const
    {
        //if the value_ is empty the expression is false.
        if (value_.empty())
            return false;

        char regex_expression[64];
        sprintf(regex_expression, "([A-Za-z0-9]*)(\\([A-Za-z0-9]*\\)){1}");

        auto is_match = std::regex_match<char>(value_.c_str(), std::regex(regex_expression));
        return is_match;
    }

    std::string get_token_value() const
    {
        return value_;
    }

protected:

    const std::string value_;// the value on the node.
};

class NodeProperties : public PropertySetBase
{
public:
    NodeProperties(std::string value, std::string parent_value, int32_t child_num)
    : PropertySetBase(value)
    , parent_value_(parent_value)
    , child_num_(child_num)
    {}
    virtual ~NodeProperties() = default;

    bool child_of_root_node() const
    {
        return (parent_value_.compare("root") == 0);
    }

    bool compare_token_label( std::string str ) const
    {
        //if the value_ is empty the expression is false.
        if (value_.empty())
            return false;

        char regex_expression[5];
        sprintf(regex_expression, "(%s)(\d*)", str.c_str());
        return ( std::regex_match<char>(value_.c_str(), std::regex(regex_expression)) );
    }

    int32_t number_of_children() const
    {
        return child_num_;
    }


private:
    const std::string parent_value_;// the value on the parent.
    const int32_t child_num_;// the number of children on the node.
};

class RecordProperties : public PropertySetBase
{
public:
    RecordProperties(NodeProperties old)
    : PropertySetBase(old.get_token_value())
    , set_position_(-1)
    , value_num_(old.number_of_children())
    {

    }

    RecordProperties(const RecordProperties &properties)
    : PropertySetBase(properties.value_)
    , set_position_(properties.set_position_)
    , value_num_(properties.value_num_)
    {}

    virtual ~RecordProperties() = default;

    int32_t number_of_values() const
    {
        return value_num_;
    }

private:
    const int32_t set_position_;// in other words the record number
    const int32_t value_num_;// number of values in the record 
};

}// namespace sdg