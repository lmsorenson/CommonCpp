// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../Reads/ReadStrategy.hpp"
#include "../Writes/WriteStrategy.hpp"



class AbstractFactory
{
public:
    virtual ReadStrategy * MakeRead() = 0;
    virtual WriteStrategy * MakeWrite() = 0;
    virtual AbstractDataStructure * MakeData() = 0;
};