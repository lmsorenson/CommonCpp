#pragma once
#include <string>
#include <iostream>
#include <deque>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "../Mocks/test_data_set.hpp"

#include "../../TestFramework.hpp"
#include "../../../../src/abstract/lexer/Lexer.hpp"
#include "../../../../src/abstract/intermediate/Stream.hpp"


class DataSetTests : public ::testing::Test
{

protected:

    DataSetTests()
    {

    }

    virtual ~DataSetTests()
    {

    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

};

TEST_F(DataSetTests, data_set_SET_function_while_good )
{
    TestDataSet dataset = TestDataSet(::sdg::DataSet::State::DATA_SET_GOOD);

    auto descA = ::sdg::hash::DescriptorInstance("A", ::sdg::Attribute::Scale::Ordinal);
    descA.set_value(1);

    auto descB = ::sdg::hash::DescriptorInstance("B", ::sdg::Attribute::Scale::Ordinal);
    descB.set_value(1);

    dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("hello world", ""));

    ASSERT_EQ("hello world",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
}

TEST_F(DataSetTests, data_set_SET_function_while_empty )
{
    TestDataSet dataset = TestDataSet();

    dataset.set(::sdg::hash::KeyInstance("A1-B1"), ::sdg::plHashValue("hello world", ""));

    ASSERT_EQ("hello world",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
}

TEST_F(DataSetTests, data_set_SET_function_default_KeyInstance )
{
    TestDataSet dataset = TestDataSet();

    auto result = dataset.set(::sdg::hash::KeyInstance(), ::sdg::plHashValue("hello world", ""));

    ASSERT_EQ(-1, result);
    ASSERT_EQ("NULL",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
}

TEST_F(DataSetTests, data_set_SET_function_displaces_a_value )
{
    TestDataSet dataset = TestDataSet();

    auto descA = ::sdg::hash::DescriptorInstance("A", ::sdg::Attribute::Scale::Ordinal);
    descA.set_value(1);

    auto descB = ::sdg::hash::DescriptorInstance("B", ::sdg::Attribute::Scale::Ordinal);
    descB.set_value(1);

    dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("hello world", ""));


    dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("new value", ""));

    ASSERT_EQ("new value",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
}



TEST_F(DataSetTests, data_set_SET_function_while_in_bad_state_returns_bad_state_status )
{
    TestDataSet dataset = TestDataSet(::sdg::DataSet::DATA_SET_BAD);

    auto descA = ::sdg::hash::DescriptorInstance("A", ::sdg::Attribute::Scale::Ordinal);
    descA.set_value(1);

    auto descB = ::sdg::hash::DescriptorInstance("B", ::sdg::Attribute::Scale::Ordinal);
    descB.set_value(1);

    auto result = dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("new value", ""));

    ASSERT_EQ("NO_FILE",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(::sdg::DataSet::DATA_SET_BAD, result);
}

TEST_F(DataSetTests, data_set_SET_function_while_in_unknown_state_returns_unknown_state_status )
{
    TestDataSet dataset = TestDataSet(::sdg::DataSet::UNKNOWN);

    auto descA = ::sdg::hash::DescriptorInstance("A", ::sdg::Attribute::Scale::Ordinal);
    descA.set_value(1);

    auto descB = ::sdg::hash::DescriptorInstance("B", ::sdg::Attribute::Scale::Ordinal);
    descB.set_value(1);

    auto result = dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("new value", ""));

    ASSERT_EQ("NULL",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(::sdg::DataSet::UNKNOWN, result);
}

