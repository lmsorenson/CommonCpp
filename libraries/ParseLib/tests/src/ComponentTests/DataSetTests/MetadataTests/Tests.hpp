#pragma once
#include <string>
#include <iostream>
#include <deque>
#include <cstdio>
#include <ctime>
#include <memory>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "../../../../src/abstract/data/meta/DataModel.hpp"

#include "../../../TestFramework.hpp"


class MetadataTests : public ::testing::Test
{

protected:

    MetadataTests()
    {

    }

    virtual ~MetadataTests()
    {

    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

};

TEST_F(MetadataTests, metadata_test_1 )
{
    ::sdg::Model model;

    model.add_thing(::std::make_shared<::sdg::Entity>("A","entity1"));
    model.add_thing(::std::make_shared<::sdg::Entity>("B","entity1"));

    ASSERT_EQ(0, 2);
}
