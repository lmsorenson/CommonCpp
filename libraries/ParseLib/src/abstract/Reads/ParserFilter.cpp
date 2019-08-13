// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ParserFilter.hpp"
#include <iostream>




using namespace std;

ParserFilter::ParserFilter(string new_filter_id)
{
    label = new_filter_id;
}
ParserFilter::~ParserFilter(){}

string ParserFilter::name()
{
    return "abstract";
}

std::string ParserFilter::GetID(int index)
{
    string out;
    out.append(label).append(to_string(index));
    return out;
}

std::string ParserFilter::GetLabel()
{
    return label;
}
