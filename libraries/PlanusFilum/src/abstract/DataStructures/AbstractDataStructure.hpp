// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include "Entity.hpp"

using namespace std;



class AbstractDataStructure
{
    vector<Entity> EntitySet;


public:
    AbstractDataStructure();
    ~AbstractDataStructure();

    virtual void assign();
};