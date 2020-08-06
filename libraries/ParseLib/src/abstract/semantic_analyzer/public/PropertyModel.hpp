// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <regex>
#include <iostream>

namespace sdg {

class PropertySetBase
{
public:
    PropertySetBase(const std::string &value)
    : value_(value)
    {}
    virtual ~PropertySetBase() = default;

    virtual void print() const = 0;

    virtual bool token_has_value() const
    {
        //if the value_ is empty the expression is false.
        if (value_.empty())
            return false;

        char regex_expression[64];
        sprintf(regex_expression, "([A-Za-z0-9]*)(\\([A-Za-z0-9\r\n,\"_-]*\\)){1}");

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
    explicit NodeProperties(const std::string &value, const std::string &parent_value, int32_t child_num);

    virtual ~NodeProperties() = default;

    virtual void print() const override;
    bool child_of_root_node() const;
    bool compare_token_label(const std::string &str) const;
    int32_t number_of_children() const;

private:
    const std::string parent_value_;// the value on the parent.
    const int32_t child_num_;// the number of children on the node.
};

}// namespace sdg