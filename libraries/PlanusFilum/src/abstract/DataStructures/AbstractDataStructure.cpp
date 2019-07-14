// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "AbstractDataStructure.hpp"
#include <iostream>

using namespace std;

AbstractDataStructure::AbstractDataStructure(int32_t hash_table_size)
: hash_table(hash_table_size)
{
    cout << "constructing data structure. . ." << endl;
}

AbstractDataStructure::~AbstractDataStructure()
{
    cout << "destructing data structure. . ." << endl;
}
