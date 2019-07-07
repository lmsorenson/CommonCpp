// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ParserFilter.hpp"
#include <iostream>




using namespace std;

ParserFilter::ParserFilter(){}
ParserFilter::~ParserFilter()
{
    cout << "deconstructing filter" << endl;
}

const char * ParserFilter::name()
{
    return "abstract";
}
