// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <regex>

namespace sdg {

class PropertySetBase
{
public:
    PropertySetBase() = default;
    virtual ~PropertySetBase() = default;

    virtual bool token_has_value()
    {
        char regex_expression[5];
        sprintf(regex_expression, "(\w*)(\(\w*\))");
        return ( std::regex_match<char>(value_.c_str(), std::regex(regex_expression)) );
    }

protected:

    std::string value_;// the value on the node.
};

class NodeProperties : public PropertySetBase
{
public:
    NodeProperties() = default;
    virtual ~NodeProperties() = default;

    bool child_of_root_node()
    {
        return (parent_value_.compare("root") == 0);
    }

    bool compare_token_label( std::string str )
    {
        char regex_expression[5];
        sprintf(regex_expression, "(%s)(\d*)");
        return ( std::regex_match<char>(value_.c_str(), std::regex(regex_expression)) );
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