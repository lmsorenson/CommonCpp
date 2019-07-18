// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/Factories/AbstractFactory.hpp"



class CSV_Factory : public AbstractFactory
{
public:
    virtual std::shared_ptr<ReadStrategy> make_read() override;
    virtual std::shared_ptr<WriteStrategy> make_write() override;
    virtual std::shared_ptr<AbstractDataStructure> make_data() override;
};