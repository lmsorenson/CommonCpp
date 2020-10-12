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

/**
 * When a relationship is constructed a link should be added to each entity in the relationship.
 */
TEST_F(MetadataRelationshipTests, metadata_test_relationship__constructor__no_id)
{
    ::std::shared_ptr<::sdg::Entity> entityA = ::std::make_shared<::sdg::Entity>("A", "entity a");
    ::std::shared_ptr<::sdg::Entity> entityB = ::std::make_shared<::sdg::Entity>("B", "entity b");

    ::std::shared_ptr<::sdg::Relationship> relationship = ::std::make_shared<::sdg::Relationship>("A-B", entityA, entityB);

    unsigned long a_expected_descriptor_count = 1;
    unsigned long a_actual_descriptor_count = entityA->num_descriptors();

    unsigned long b_expected_descriptor_count = 1;
    unsigned long b_actual_descriptor_count = entityB->num_descriptors();

    ASSERT_EQ(a_actual_descriptor_count, a_expected_descriptor_count);
    ASSERT_EQ(b_actual_descriptor_count, b_expected_descriptor_count);
}

TEST_F(MetadataRelationshipTests, metadata_test_relationship__constructor__ID_link_1)
{
    ::std::shared_ptr<::sdg::Entity> entityA = ::std::make_shared<::sdg::Entity>("A", "entity a");
    ::std::shared_ptr<::sdg::Entity> entityB = ::std::make_shared<::sdg::Entity>("B", "entity b");

    ::std::shared_ptr<::sdg::Relationship> relationship = ::std::make_shared<::sdg::Relationship>("A-B", entityA, entityB, false, ::sdg::Relationship::IDENTIFY_BY::LINK_1);

    unsigned long a_expected_descriptor_count = 1;
    unsigned long a_actual_descriptor_count = entityA->num_descriptors();

    unsigned long a_expected_id_descriptor_count = 1;
    unsigned long a_actual_id_descriptor_count = entityA->num_identifying_descriptors();

    unsigned long b_expected_descriptor_count = 1;
    unsigned long b_actual_descriptor_count = entityB->num_descriptors();

    unsigned long b_expected_id_descriptor_count = 0;
    unsigned long b_actual_id_descriptor_count = entityB->num_identifying_descriptors();

    ASSERT_EQ(a_actual_descriptor_count, a_expected_descriptor_count);
    ASSERT_EQ(a_actual_id_descriptor_count, a_expected_id_descriptor_count);
    ASSERT_EQ(b_actual_descriptor_count, b_expected_descriptor_count);
    ASSERT_EQ(b_actual_id_descriptor_count, b_expected_id_descriptor_count);
}

TEST_F(MetadataRelationshipTests, metadata_test_relationship__constructor__ID_link_2)
{
    ::std::shared_ptr<::sdg::Entity> entityA = ::std::make_shared<::sdg::Entity>("A", "entity a");
    ::std::shared_ptr<::sdg::Entity> entityB = ::std::make_shared<::sdg::Entity>("B", "entity b");

    ::std::shared_ptr<::sdg::Relationship> relationship = ::std::make_shared<::sdg::Relationship>("A-B", entityA, entityB, false, ::sdg::Relationship::IDENTIFY_BY::LINK_2);

    unsigned long a_expected_descriptor_count = 1;
    unsigned long a_actual_descriptor_count = entityA->num_descriptors();

    unsigned long a_expected_id_descriptor_count = 0;
    unsigned long a_actual_id_descriptor_count = entityA->num_identifying_descriptors();

    unsigned long b_expected_descriptor_count = 1;
    unsigned long b_actual_descriptor_count = entityB->num_descriptors();

    unsigned long b_expected_id_descriptor_count = 1;
    unsigned long b_actual_id_descriptor_count = entityB->num_identifying_descriptors();

    ASSERT_EQ(a_actual_descriptor_count, a_expected_descriptor_count);
    ASSERT_EQ(a_actual_id_descriptor_count, a_expected_id_descriptor_count);
    ASSERT_EQ(b_actual_descriptor_count, b_expected_descriptor_count);
    ASSERT_EQ(b_actual_id_descriptor_count, b_expected_id_descriptor_count);
}