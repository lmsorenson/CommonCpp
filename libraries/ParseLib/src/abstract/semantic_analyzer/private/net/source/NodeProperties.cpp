// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../../../public/PropertyModel.hpp"

using ::sdg::NodeProperties;
using ::std::cout;

NodeProperties::NodeProperties(const std::string &value, const std::string &parent_value, int32_t child_num)
        : PropertySetBase(value), parent_value_(parent_value), child_num_(child_num) {}


void NodeProperties::print() const {
    cout << "value: " << value_ << " parent value: " << parent_value_ << " child num: " << child_num_;
}

bool NodeProperties::child_of_root_node() const {
    return (parent_value_.compare("root") == 0);
}

bool NodeProperties::compare_token_label(const std::string &str) const {
    //if the value_ is empty the expression is false.
    if (value_.empty())
        return false;

    char regex_expression[16];
    sprintf(regex_expression, "(%s)(\\d*)", str.c_str());
    return (std::regex_match<char>(value_.c_str(), std::regex(regex_expression)));
}

int32_t NodeProperties::number_of_children() const {
    return child_num_;
}