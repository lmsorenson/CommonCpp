#include "Tests.hpp"
#include <gtest/gtest.h>


TEST_F(DataSetTests, dataset__is_descriptor_required__finds_required_descriptor )
{
    MockDataSet dataset = MockDataSet();

    auto result = dataset.is_descriptor_required(::sdg::hash::DescriptorID("B"));

    //result of 1 means required.
    ASSERT_EQ(result, 1);
}

TEST_F(DataSetTests, dataset__IsDescriptorRequired__unrequired_descriptor_returns_false )
{
    MockDataSet dataset = MockDataSet();

    auto result = dataset.is_descriptor_required(::sdg::hash::DescriptorID("U"));

    //result of -1 means error.
    ASSERT_EQ(result, 0);
}

TEST_F(DataSetTests, dataset__IsDescriptorRequired__nonexistant_descriptor_returns_error )
{
    MockDataSet dataset = MockDataSet();

    auto result = dataset.is_descriptor_required(::sdg::hash::DescriptorID("Z"));

    //result of -1 means error.
    ASSERT_EQ(result, -1);
}

TEST_F(DataSetTests, dataset__zx__nonexistant_descriptor_returns_error )
{
    MockDataSet dataset = MockDataSet();

    ::sdg::Instance result = dataset.where(::sdg::hash::KeyInstance("Z0-X0"), "some-value");

    //result of -1 means error.
    ASSERT_EQ(result.get(), "NULL");
}