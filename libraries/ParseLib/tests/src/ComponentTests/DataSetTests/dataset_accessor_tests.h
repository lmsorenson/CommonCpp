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

TEST_F(DataSetTests, dataset__WHERE__key_doesnt_exist )
{
    MockDataSet dataset = MockDataSet();

    ::sdg::Instance result = dataset.where(::sdg::hash::KeyInstance("Z0-X0"), "some-value");

    //result of -1 means error.
    ASSERT_EQ(result.get(), "NULL");
}

TEST_F(DataSetTests, dataset__WHERE__key_exists )
{
    MockDataSet dataset = MockDataSet();

    dataset.set(::sdg::hash::KeyInstance("A1-B0"), ::sdg::plHashValue("value", ""));
    dataset.set(::sdg::hash::KeyInstance("A1-B1"), ::sdg::plHashValue("key", ""));
    dataset.set(::sdg::hash::KeyInstance("A1-B2"), ::sdg::plHashValue("value", ""));

    ::sdg::Instance result = dataset.where(::sdg::hash::KeyInstance("A1"), "key");

    //result of -1 means error.
    ASSERT_EQ(result.get(), "key");
}