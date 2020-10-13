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

    virtual std::shared_ptr<class ReadStrategy> make_read() const = 0;
    virtual std::shared_ptr<class WriteStrategy> make_write() const = 0;
    virtual std::shared_ptr<class DataSet> make_data() const = 0;
};

}// namespace sdg