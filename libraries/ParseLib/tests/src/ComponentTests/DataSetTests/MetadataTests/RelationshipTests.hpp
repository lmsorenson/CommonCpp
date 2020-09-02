#pragma once
#include <string>
#include <iostream>
#include <deque>
#include <cstdio>
#include <ctime>
#include <memory>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "../../../../src/abstract/data/meta/Relationship.hpp"

#include "../../../TestFramework.hpp"


class MetadataRelationshipTests : public ::testing::Test
{

protected:

    MetadataRelationshipTests()
    {

    }

    virtual ~MetadataRelationshipTests()
    {

    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

};

TEST_F(MetadataRelationshipTests, metadata_test_entity_doesnt_exist )
{
    ASSERT_EQ(1, 2);
}