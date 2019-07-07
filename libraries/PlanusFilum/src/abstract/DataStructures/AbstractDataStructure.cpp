// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "AbstractDataStructure.hpp"
#include <iostream>

using namespace std;

AbstractDataStructure::AbstractDataStructure()
{
    cout << "constructing data structure. . ." << endl;
}

AbstractDataStructure::~AbstractDataStructure()
{
    cout << "destructing data structure. . ." << endl;
}

void AbstractDataStructure::assign()
{
    cout << "Abstract Data" << endl;
}