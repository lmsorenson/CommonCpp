// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/Factories/AbstractFactory.hpp"



class CSV_Factory : public AbstractFactory
{
public:
    virtual std::shared_ptr<ReadStrategy> MakeRead() override;
    virtual std::shared_ptr<WriteStrategy> MakeWrite() override;
    virtual std::shared_ptr<AbstractDataStructure> MakeData() override;
};