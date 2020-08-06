// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../hash_table.hpp"


using std::string;
using sdg::plHashValue;



plHashValue::plHashValue()
: value("")
, parent_key("")
{}
plHashValue::plHashValue(const string &aValue, const string &aParentString)
: value(aValue)
, parent_key(aParentString)
{}
plHashValue::~plHashValue()
{}

bool plHashValue::is_valid()
{
    return !(value.empty() && parent_key.empty());
}

string plHashValue::get_value() const
{
    return value;
}

void plHashValue::clear_hash_value()
{
    value.clear();
    parent_key.clear();
}