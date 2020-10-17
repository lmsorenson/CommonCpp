#pragma once
#include <ParseLib.hpp>
#include <gmock/gmock.h>
#include <memory>

#include "../src/abstract/Factories/AbstractFactory.hpp"


class MockFacade : public ::sdg::ParseLib
{
public:
    MockFacade() = default;
    virtual ~MockFacade() = default;

    MOCK_METHOD(int32_t, read_file, (sdg::DataSet& data_store, const char * filepath, std::vector<::sdg::option> read_options), (override));
    MOCK_METHOD(int32_t, write_file, (sdg::DataSet& data_store, const char * filepath, std::vector<::sdg::option> read_options), (override));
    MOCK_METHOD(::std::shared_ptr<::sdg::AbstractFactory>, produce_factory, (), (const override));
};

