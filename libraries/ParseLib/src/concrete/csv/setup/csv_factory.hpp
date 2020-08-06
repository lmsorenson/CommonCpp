// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../../abstract/Factories/AbstractFactory.hpp"



namespace sdg {
namespace csv {

class Factory : public sdg::AbstractFactory
{
public:
    Factory() = default;
    virtual ~Factory() = default;

    virtual std::shared_ptr<sdg::ReadStrategy> make_read() override;
    virtual std::shared_ptr<sdg::WriteStrategy> make_write() override;
    virtual std::shared_ptr<sdg::DataSet> make_data() override;
};

}// namespace csv
}// namespace sdg