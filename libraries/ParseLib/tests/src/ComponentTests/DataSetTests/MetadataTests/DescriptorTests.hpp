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

/**
 *
 */
TEST_F(MetadataDescriptorTests, link_get_identifying_descriptor_ids )
{
    ::std::shared_ptr<::sdg::Entity> entityA = ::std::make_shared<::sdg::Entity>("A", "entity a");
    ::std::shared_ptr<::sdg::Attribute> a_id_attribute;

    entityA->add_descriptor(a_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id_1", "A1", ::sdg::Attribute::Scale::Ordinal)), true);
    entityA->add_descriptor(a_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id_2", "A2", ::sdg::Attribute::Scale::Ordinal)), true);
    entityA->add_descriptor(a_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_desc_3", "A3", ::sdg::Attribute::Scale::Ordinal)), false);

    ::std::shared_ptr<::sdg::Link> link = ::std::make_shared<::sdg::Link>("link", entityA);

    ::std::vector<::sdg::hash::DescriptorID> actual_identifier = link->get_identifying_descriptor_IDs();
    ::std::vector<::sdg::hash::DescriptorID> expected_identifier
    {
            ::sdg::hash::DescriptorID("A1"),
            ::sdg::hash::DescriptorID("A2")
    };

    ASSERT_THAT(actual_identifier, ::testing::ContainerEq(expected_identifier));
}

/**
 *
 */
TEST_F(MetadataDescriptorTests, link_get_descriptor_ids )
{
    ::std::shared_ptr<::sdg::Entity> entityA = ::std::make_shared<::sdg::Entity>("A", "entity a");
    ::std::shared_ptr<::sdg::Attribute> a_id_1_attribute;
    ::std::shared_ptr<::sdg::Attribute> a_id_2_attribute;
    ::std::shared_ptr<::sdg::Attribute> a_desc_3_attribute;

    entityA->add_descriptor(a_id_1_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id_1", "A1", ::sdg::Attribute::Scale::Ordinal)), true);
    entityA->add_descriptor(a_id_2_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id_2", "A2", ::sdg::Attribute::Scale::Ordinal)), true);
    entityA->add_descriptor(a_desc_3_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_desc_3", "A3", ::sdg::Attribute::Scale::Ordinal)), false);

    ::std::shared_ptr<::sdg::Link> link = ::std::make_shared<::sdg::Link>("link", entityA);

    ::std::vector<::std::shared_ptr<::sdg::Descriptor>> actual_identifier = link->get_identifying_descriptors();
    ::std::vector<::std::shared_ptr<::sdg::Descriptor>> expected_identifier
    {
        a_id_1_attribute,
        a_id_2_attribute
    };

    ASSERT_THAT(actual_identifier, ::testing::ContainerEq(expected_identifier));
}