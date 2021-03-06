// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../Reads/ReadStrategy.hpp"
#include "../Writes/WriteStrategy.hpp"


namespace sdg
{

class AbstractFactory
{
public:
    AbstractFactory() = default;
    virtual ~AbstractFactory() = default;

    virtual std::shared_ptr<ReadStrategy> make_read() = 0;
    virtual std::shared_ptr<WriteStrategy> make_write() = 0;
    virtual std::shared_ptr<sdg::DataSet> make_data() = 0;
};

}// namespace sdg