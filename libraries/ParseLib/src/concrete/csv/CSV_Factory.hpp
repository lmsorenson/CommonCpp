// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/Factories/AbstractFactory.hpp"



class CSV_Factory : public sdg::AbstractFactory
{
public:
    virtual std::shared_ptr<sdg::ReadStrategy> make_read() override;
    virtual std::shared_ptr<WriteStrategy> make_write() override;
    virtual std::shared_ptr<sdg::DataSet> make_data() override;
};