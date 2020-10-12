#pragma once
#include <string>
#include <iostream>
#include <deque>
#include <cstdio>
#include <ctime>
#include <memory>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include <Entity.hpp>

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

TEST_F(MetadataEntityTests, metadata_test_entity_get_identifying_descriptor_id_set )
{
    ::std::shared_ptr<::sdg::Entity> entityA = ::std::make_shared<::sdg::Entity>("A", "entity a");
    ::std::shared_ptr<::sdg::Attribute> a_id_attribute;

    entityA->add_descriptor(a_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id_1", "A1", ::sdg::Attribute::Scale::Ordinal)), true);
    entityA->add_descriptor(a_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id_2", "A2", ::sdg::Attribute::Scale::Ordinal)), true);
    entityA->add_descriptor(a_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_desc_3", "A3", ::sdg::Attribute::Scale::Ordinal)), false);

    ::std::vector<::sdg::hash::DescriptorID> actual_identifier = entityA->get_identifying_descriptor_id_set();
    ::std::vector<::sdg::hash::DescriptorID> expected_identifier
    {
            ::sdg::hash::DescriptorID("A1"),
            ::sdg::hash::DescriptorID("A2")
    };

    ASSERT_THAT(actual_identifier, ::testing::ContainerEq(expected_identifier));
}


TEST_F(MetadataEntityTests, metadata_test_entity_get_identifying_descriptor_set )
{
    ::std::shared_ptr<::sdg::Entity> entityA = ::std::make_shared<::sdg::Entity>("A", "entity a");
    ::std::shared_ptr<::sdg::Attribute> a_id_1_attribute;
    ::std::shared_ptr<::sdg::Attribute> a_id_2_attribute;
    ::std::shared_ptr<::sdg::Attribute> a_desc_3_attribute;

    entityA->add_descriptor(a_id_1_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id_1", "A1", ::sdg::Attribute::Scale::Ordinal)), true);
    entityA->add_descriptor(a_id_2_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id_2", "A2", ::sdg::Attribute::Scale::Ordinal)), true);
    entityA->add_descriptor(a_desc_3_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_desc_3", "A3", ::sdg::Attribute::Scale::Ordinal)), false);

    ::std::vector<::std::shared_ptr<::sdg::Descriptor>> actual_identifier = entityA->get_identifying_descriptor_set();
    ::std::vector<::std::shared_ptr<::sdg::Descriptor>> expected_identifier
    {
            a_id_1_attribute,
            a_id_2_attribute
    };

    ASSERT_THAT(actual_identifier, ::testing::ContainerEq(expected_identifier));
}

TEST_F(MetadataEntityTests, link_get_identifying_descriptor_ids )
{
    ::std::shared_ptr<::sdg::Entity> entityA = ::std::make_shared<::sdg::Entity>("A", "entity a");
    ::std::shared_ptr<::sdg::Attribute> a_id_attribute;

    entityA->add_descriptor(a_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id_1", "A1", ::sdg::Attribute::Scale::Ordinal)), true);
    entityA->add_descriptor(a_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id_2", "A2", ::sdg::Attribute::Scale::Ordinal)), true);
    entityA->add_descriptor(a_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_desc_3", "A3", ::sdg::Attribute::Scale::Ordinal)), false);

    ::std::shared_ptr<::sdg::Entity> entityB = ::std::make_shared<::sdg::Entity>("B", "entity b");
    ::std::shared_ptr<::sdg::Link> link = ::std::make_shared<::sdg::Link>("link", entityA);

    entityB->add_descriptor(link, true);

    ::std::vector<::sdg::hash::DescriptorID> actual_identifier = entityB->get_identifying_descriptor_id_set();
    ::std::vector<::sdg::hash::DescriptorID> expected_identifier
        {
                ::sdg::hash::DescriptorID("A1"),
                ::sdg::hash::DescriptorID("A2")
        };

    ASSERT_THAT(actual_identifier, ::testing::ContainerEq(expected_identifier));
}

TEST_F(MetadataEntityTests, metadata_test_entity__add_descriptor__index_in_range )
{
    ::std::shared_ptr<::sdg::Entity> entityA = ::std::make_shared<::sdg::Entity>("A", "entity a");
    ::std::shared_ptr<::sdg::Attribute> a_id_1_attribute;

    entityA->add_descriptor(a_id_1_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id_1", "A1", ::sdg::Attribute::Scale::Ordinal)), true);

    unsigned long expected_num_descriptors = 1;
    unsigned long actual_num_descriptors = entityA->num_descriptors();

    ASSERT_EQ(actual_num_descriptors, expected_num_descriptors);
}

TEST_F(MetadataEntityTests, metadata_test_entity__add_descriptor__index_out_of_range )
{
    ::std::shared_ptr<::sdg::Entity> entityA = ::std::make_shared<::sdg::Entity>("A", "entity a");
    ::std::shared_ptr<::sdg::Attribute> a_id_1_attribute;

    entityA->add_descriptor(a_id_1_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id_1", "A1", ::sdg::Attribute::Scale::Ordinal)), true, 2);

    unsigned long expected_num_descriptors = 0;
    unsigned long actual_num_descriptors = entityA->num_identifying_descriptors();

    ASSERT_EQ(actual_num_descriptors, expected_num_descriptors);
}