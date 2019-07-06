#pragma once
#include "../../abstract/Factories/AbstractFactory.hpp"



class CSV_Factory : public AbstractFactory
{
public:
    virtual ReadStrategy * MakeRead() override;
    virtual WriteStrategy * MakeWrite() override;
    virtual AbstractDataStructure * MakeData() override;
};