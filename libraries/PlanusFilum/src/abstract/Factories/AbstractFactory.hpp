// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../Reads/ReadStrategy.hpp"
#include "../Writes/WriteStrategy.hpp"



class AbstractFactory
{
public:
    virtual std::shared_ptr<ReadStrategy> MakeRead() = 0;
    virtual std::shared_ptr<WriteStrategy> MakeWrite() = 0;
    virtual std::shared_ptr<AbstractDataStructure> MakeData() = 0;
};