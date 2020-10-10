#pragma once
#include <string>
#include <iostream>
#include <deque>
#include <cstdio>
#include <ctime>
#include <memory>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "../../../../src/abstract/data/meta/Interface.hpp"

#include "../../../TestFramework.hpp"


class MetadataThingTests : public ::testing::Test
{

protected:

    MetadataThingTests()
    {

    }

    virtual ~MetadataThingTests()
    {

    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

};

TEST_F(MetadataThingTests, metadata_test_entity_doesnt_exist )
{
    ASSERT_EQ(1, 2);
}