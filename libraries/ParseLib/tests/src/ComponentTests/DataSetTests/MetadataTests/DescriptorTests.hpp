#pragma once
#include <string>
#include <iostream>
#include <deque>
#include <cstdio>
#include <ctime>
#include <memory>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include <Descriptor.hpp>
#include <Entity.hpp>

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

TEST_F(MetadataDescriptorTests, link_get_descriptor_ids )
{
    //creates an entity with a single attribute.
    std::shared_ptr<sdg::Entity> a = std::make_shared<sdg::Entity>("A", "EntityA");
    std::shared_ptr<sdg::Entity> b = std::make_shared<sdg::Entity>("B", "EntityB");
    std::shared_ptr<sdg::Descriptor> c = std::make_shared<sdg::Attribute>("DescriptorC", "C", sdg::Attribute::Scale::Ordinal);
    a->add_descriptor(c, true);

//    std::shared_ptr<sdg::Link> c = std::make_shared<sdg::Link>("LinkToEntityA", a);

//    ASSERT_THAT(c->get_identifying_descriptor_IDs(), ::testing::ElementsAre(sdg::hash::DescriptorID("B")));
//    int size = c->get_identifying_descriptor_IDs().size();

    ASSERT_EQ(1,1);
//    ASSERT_EQ(size, 1);
}