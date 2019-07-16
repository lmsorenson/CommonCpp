// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ParserFilter.hpp"
#include <iostream>




using namespace std;

ParserFilter::ParserFilter(string new_filter_id)
{
    id = new_filter_id;
}
ParserFilter::~ParserFilter()
{
    cout << "deconstructing filter" << endl;
}

const char * ParserFilter::name()
{
    return "abstract";
}

std::string ParserFilter::GetID(int index)
{
    string out;
    out.append(id).append(to_string(index));
    return out;
}
