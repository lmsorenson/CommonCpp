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

    MOCK_METHOD(::std::shared_ptr<::sdg::AbstractFactory>, produce_factory, (), (const override));
};

