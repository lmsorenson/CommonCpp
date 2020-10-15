#pragma once
#include <string>
#include <iostream>
#include <deque>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include <objects/data_set.hpp>
#include "../Mocks/mock_data_set.hpp"
//#include "../Mocks/mock_facade.hpp"
//#include "../Mocks/mock_abstract_factory.hpp"
//#include "../Mocks/mock_read_strategy.hpp"
//#include "../Mocks/mock_write_strategy.hpp"

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

TEST_F(DataSetTests, data_set__SET__function_while_good )
{
    MockDataSet dataset = MockDataSet(::sdg::DataSet::State::DATA_SET_GOOD);

    auto descA = ::sdg::hash::DescriptorInstance("A", ::sdg::Attribute::Scale::Ordinal);
    descA.set_value(1);

    auto descB = ::sdg::hash::DescriptorInstance("B", ::sdg::Attribute::Scale::Ordinal);
    descB.set_value(1);

    auto result = dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("hello world", ""));

    ASSERT_EQ("hello world",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(0, result);
}

TEST_F(DataSetTests, data_set__SET__function_while_empty )
{
    MockDataSet dataset = MockDataSet();

    auto result = dataset.set(::sdg::hash::KeyInstance("A1-B1"), ::sdg::plHashValue("hello world", ""));

    ASSERT_EQ("hello world",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(0, result);
}

TEST_F(DataSetTests, data_set__SET__function_default_KeyInstance )
{
    MockDataSet dataset = MockDataSet();

    auto result = dataset.set(::sdg::hash::KeyInstance(), ::sdg::plHashValue("hello world", ""));


    ASSERT_EQ("NULL",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(-1, result);
}

TEST_F(DataSetTests, data_set__SET__function_default_hashValue )
{
    MockDataSet dataset = MockDataSet();

    auto result = dataset.set(::sdg::hash::KeyInstance("A1-B1"), ::sdg::plHashValue());

    ASSERT_EQ("",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(0, result);
}

TEST_F(DataSetTests, data_set__SET__function_overwrites_a_value )
{
    ::sdg::DataSet dataset = ::sdg::DataSet();

    auto descA = ::sdg::hash::DescriptorInstance("A", ::sdg::Attribute::Scale::Ordinal);
    descA.set_value(1);

    auto descB = ::sdg::hash::DescriptorInstance("B", ::sdg::Attribute::Scale::Ordinal);
    descB.set_value(1);

    dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("hello world", ""));


    auto result = dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("new value", ""));

    ASSERT_EQ("new value",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(0, result);
}



TEST_F(DataSetTests, data_set__SET__function_while_in_bad_state_returns_bad_state_status )
{
    MockDataSet dataset = MockDataSet(::sdg::DataSet::DATA_SET_BAD);

    auto descA = ::sdg::hash::DescriptorInstance("A", ::sdg::Attribute::Scale::Ordinal);
    descA.set_value(1);

    auto descB = ::sdg::hash::DescriptorInstance("B", ::sdg::Attribute::Scale::Ordinal);
    descB.set_value(1);

    auto result = dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("new value", ""));

    ASSERT_EQ("NO_FILE",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(::sdg::DataSet::DATA_SET_BAD, result);
}

TEST_F(DataSetTests, data_set__SET__function_while_in_unknown_state_returns_unknown_state_status )
{
    MockDataSet dataset = MockDataSet(::sdg::DataSet::UNKNOWN);

    auto descA = ::sdg::hash::DescriptorInstance("A", ::sdg::Attribute::Scale::Ordinal);
    descA.set_value(1);

    auto descB = ::sdg::hash::DescriptorInstance("B", ::sdg::Attribute::Scale::Ordinal);
    descB.set_value(1);

    auto result = dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("new value", ""));

    ASSERT_EQ("NULL",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(::sdg::DataSet::UNKNOWN, result);
}

TEST_F(DataSetTests, data_set__SET__WITH_DESCRIPTOR_function_while_good )
{
    MockDataSet dataset = MockDataSet(::sdg::DataSet::State::DATA_SET_GOOD);

    auto descA = ::sdg::hash::DescriptorInstance("A", ::sdg::Attribute::Scale::Ordinal);
    descA.set_value(1);

    auto descB = ::sdg::hash::DescriptorInstance("B", ::sdg::Attribute::Scale::Ordinal);
    descB.set_value(1);

    auto result = dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("hello world", ""), ::sdg::hash::DescriptorID("A"));

    ASSERT_EQ("hello world",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(0, result);
}

TEST_F(DataSetTests, data_set__SET__WITH_DESCRIPTOR_function_while_empty )
{
    MockDataSet dataset = MockDataSet();

    auto result = dataset.set(::sdg::hash::KeyInstance("A1-B1"), ::sdg::plHashValue("hello world", ""), ::sdg::hash::DescriptorID("A"));

    ASSERT_EQ("hello world",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(0, result);
}

TEST_F(DataSetTests, data_set__SET__WITH_DESCRIPTOR_function_default_KeyInstance )
{
    MockDataSet dataset = MockDataSet();

    auto result = dataset.set(::sdg::hash::KeyInstance(), ::sdg::plHashValue("hello world", ""), ::sdg::hash::DescriptorID("A"));


    ASSERT_EQ("NULL",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(-1, result);
}

TEST_F(DataSetTests, data_set__SET__WITH_DESCRIPTOR_function_default_hashValue )
{
    MockDataSet dataset = MockDataSet();

    auto result = dataset.set(::sdg::hash::KeyInstance("A1-B1"), ::sdg::plHashValue(), ::sdg::hash::DescriptorID("A"));

    ASSERT_EQ("",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(0, result);
}

TEST_F(DataSetTests, data_set__SET__WITH_DESCRIPTOR_function_overwrites_a_value )
{
    MockDataSet dataset = MockDataSet();

    auto descA = ::sdg::hash::DescriptorInstance("A", ::sdg::Attribute::Scale::Numeric);
    descA.set_value(1);

    auto descB = ::sdg::hash::DescriptorInstance("B", ::sdg::Attribute::Scale::Numeric);
    descB.set_value(1);

    dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("hello world", ""));


    auto result = dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("new value", ""), ::sdg::hash::DescriptorID("A"));

    ASSERT_EQ("hello world",dataset.get(::sdg::hash::KeyInstance("A2-B1")).get());
    ASSERT_EQ(0, result);
}



TEST_F(DataSetTests, data_set__SET__WITH_DESCRIPTOR_function_while_in_bad_state_returns_bad_state_status )
{
    MockDataSet dataset = MockDataSet(::sdg::DataSet::DATA_SET_BAD);

    auto descA = ::sdg::hash::DescriptorInstance("A", ::sdg::Attribute::Scale::Ordinal);
    descA.set_value(1);

    auto descB = ::sdg::hash::DescriptorInstance("B", ::sdg::Attribute::Scale::Ordinal);
    descB.set_value(1);

    auto result = dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("new value", ""), ::sdg::hash::DescriptorID("A"));

    ASSERT_EQ("NO_FILE",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(::sdg::DataSet::DATA_SET_BAD, result);
}

TEST_F(DataSetTests, data_set__SET__WITH_DESCRIPTOR_function_while_in_unknown_state_returns_unknown_state_status )
{
    MockDataSet dataset = MockDataSet(::sdg::DataSet::UNKNOWN);

    auto descA = ::sdg::hash::DescriptorInstance("A", ::sdg::Attribute::Scale::Ordinal);
    descA.set_value(1);

    auto descB = ::sdg::hash::DescriptorInstance("B", ::sdg::Attribute::Scale::Ordinal);
    descB.set_value(1);

    auto result = dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("new value", ""), ::sdg::hash::DescriptorID("A"));

    ASSERT_EQ("NULL",dataset.get(::sdg::hash::KeyInstance("A1-B1")).get());
    ASSERT_EQ(::sdg::DataSet::UNKNOWN, result);
}

TEST_F(DataSetTests, data_set__DEFAULT_CONSTRUCTOR__does_not_create_fatal_error )
{
    ASSERT_NO_FATAL_FAILURE({
        MockDataSet dataset = MockDataSet();
    });
}

TEST_F(DataSetTests, data_set__INITIAL_STATE_CONSTRUCTOR__does_not_create_fatal_error )
{
    ASSERT_NO_FATAL_FAILURE({
        MockDataSet dataset = MockDataSet(::sdg::DataSet::State::DATA_SET_GOOD);
    });
}

TEST_F(DataSetTests, data_set__INDEX_OPERATOR__)
{
    MockDataSet dataset = MockDataSet(::sdg::DataSet::UNKNOWN);

    auto descA = ::sdg::hash::DescriptorInstance("A", ::sdg::Attribute::Scale::Ordinal);
    descA.set_value(1);

    auto descB = ::sdg::hash::DescriptorInstance("B", ::sdg::Attribute::Scale::Ordinal);
    descB.set_value(1);

    auto result = dataset.set(::sdg::hash::KeyInstance({descA,descB}), ::sdg::plHashValue("new value", ""), ::sdg::hash::DescriptorID("A"));

    ASSERT_EQ("NULL",dataset["A1"]["B1"].get());
    ASSERT_EQ(::sdg::DataSet::UNKNOWN, result);
}

TEST_F(DataSetTests, data_set__READ__returns_an_unknown_error)
{
//    ::std::shared_ptr<MockFacade> mockParseLib = ::std::make_shared<MockFacade>();
//    ::std::shared_ptr<MockAbstractFactory> mockFactory = ::std::make_shared<MockAbstractFactory>();
//    ::std::shared_ptr<MockReadStrategy> mockRead = ::std::make_shared<MockReadStrategy>();
//    MockWriteStrategy mockWrite = MockWriteStrategy();
//
    ::std::shared_ptr<MockDataSet> mock_data_set = ::std::make_shared<MockDataSet>();
//    mock_data_set->use_mock_facade(mockParseLib);
//
//    ::std::vector<::sdg::option> options;
//    ON_CALL(*mockRead, execute_read).WillByDefault(::testing::Return(-1));
//    ON_CALL(*mockFactory, make_read).WillByDefault(::testing::Return(mockRead));
//    ON_CALL(*mockFactory, make_data()).WillByDefault(::testing::Return(mock_data_set));
//    ON_CALL(*mockParseLib, produce_factory).WillByDefault(::testing::Return(mockFactory));

    int32_t err = 0;
    mock_data_set->Read("path/to/file", &err);
//    ASSERT_EQ(err, 4);
}

//TEST_F(DataSetTests, data_set__READ__returns_an_an_invalid_format_error)
//{
//    ::std::shared_ptr<MockFacade> mockParseLib = ::std::make_shared<MockFacade>();
//    ::std::shared_ptr<MockAbstractFactory> mockFactory = ::std::make_shared<MockAbstractFactory>();
//    ::std::shared_ptr<MockReadStrategy> mockRead = ::std::make_shared<MockReadStrategy>();
//    MockWriteStrategy mockWrite = MockWriteStrategy();
//
//    ::std::shared_ptr<MockDataSet> mock_data_set = ::std::make_shared<MockDataSet>();
//    mock_data_set->use_mock_facade(mockParseLib);
//
//    ::std::vector<::sdg::option> options;
//    ON_CALL(*mockRead, execute_read).WillByDefault(::testing::Return(2));
//    ON_CALL(*mockFactory, make_read).WillByDefault(::testing::Return(mockRead));
//    ON_CALL(*mockFactory, make_data()).WillByDefault(::testing::Return(mock_data_set));
//    ON_CALL(*mockParseLib, produce_factory).WillByDefault(::testing::Return(mockFactory));
//
//    int32_t err = 0;
//    mock_data_set->Read("path/to/file", &err);
//    ASSERT_EQ(err, 1);
//}

TEST_F(DataSetTests, data_set__READ__pass_in_options)
{
    ::sdg::DataSet dataset = ::sdg::DataSet();

    std::vector<::sdg::option> options;
    int32_t err;

    ASSERT_NO_FATAL_FAILURE({
        dataset.Read("path/to/file", options, &err);
    });
}

TEST_F(DataSetTests, data_set__Write__)
{
    ::sdg::DataSet dataset = ::sdg::DataSet();

    int32_t err;

    ASSERT_NO_FATAL_FAILURE({
        dataset.Write("path/to/file", &err);
    });
}

TEST_F(DataSetTests, data_set__Write__pass_in_options)
{
    ::sdg::DataSet dataset = ::sdg::DataSet();

    std::vector<::sdg::option> options;
    int32_t err;

    ASSERT_NO_FATAL_FAILURE({
        dataset.Write("path/to/file", options, &err);
    });
}