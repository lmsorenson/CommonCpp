#pragma once
#include <string>
#include <iostream>
#include <deque>
#include <cstdio>
#include <ctime>
#include <memory>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "../../../../src/abstract/data/meta/Descriptor.hpp"

#include "../../../TestFramework.hpp"


class MetadataDescriptorTests : public ::testing::Test
{

protected:

    MetadataDescriptorTests()
    {

    }

    virtual ~MetadataDescriptorTests()
    {

    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

};

TEST_F(MetadataDescriptorTests, metadata_test_entity_doesnt_exist )
{
    ASSERT_EQ(1, 2);
}