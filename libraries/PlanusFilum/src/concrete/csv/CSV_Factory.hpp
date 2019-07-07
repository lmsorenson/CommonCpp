// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/Factories/AbstractFactory.hpp"



class CSV_Factory : public AbstractFactory
{
public:
    virtual ReadStrategy * MakeRead() override;
    virtual WriteStrategy * MakeWrite() override;
    virtual AbstractDataStructure * MakeData() override;
};