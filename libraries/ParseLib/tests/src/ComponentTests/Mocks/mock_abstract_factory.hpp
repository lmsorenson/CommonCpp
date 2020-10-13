#pragma once
#include "../src/abstract/Factories/AbstractFactory.hpp"
#include <gmock/gmock.h>
#include <memory>






class MockAbstractFactory : public ::sdg::AbstractFactory
{
public:
    MockAbstractFactory() = default;
    virtual ~MockAbstractFactory() = default;

    MOCK_METHOD(::std::shared_ptr<::sdg::ReadStrategy>, make_read, (), (const override));
    MOCK_METHOD(::std::shared_ptr<::sdg::WriteStrategy>, make_write, (), (const override));
    MOCK_METHOD(::std::shared_ptr<::sdg::DataSet>, make_data, (), (const override));
};
