#pragma once
#include <string>
#include <iostream>
#include <deque>
#include <cstdio>
#include <ctime>
#include <memory>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "../../../../src/abstract/data/meta/Entity.hpp"

#include "../../../TestFramework.hpp"


class MetadataEntityTests : public ::testing::Test
{

protected:

    MetadataEntityTests()
    {

    }

    virtual ~MetadataEntityTests()
    {

    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

};

TEST_F(MetadataEntityTests, metadata_test_entity_doesnt_exist )
{
    ASSERT_EQ(1, 2);
}