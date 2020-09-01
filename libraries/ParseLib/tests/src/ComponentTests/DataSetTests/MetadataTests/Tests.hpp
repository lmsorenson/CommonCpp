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

TEST_F(MetadataTests, metadata_add_two_entities_with_the_same_id )
{
    ::sdg::Model model;

    ::std::shared_ptr<::sdg::Entity>
            entityA = ::std::make_shared<::sdg::Entity>("G", "entity a"),
            entityB = ::std::make_shared<::sdg::Entity>("G", "entity b");

    model.add_thing(entityA);
    auto result = model.add_thing(entityB);

    ASSERT_EQ(1, model.size());
    ASSERT_EQ(1, result);
}

TEST_F(MetadataTests, metadata_test_1 )
{
    ::sdg::Model model;

    ::std::shared_ptr<::sdg::Entity>
            entityA = ::std::make_shared<::sdg::Entity>("A", "entity a"),
            entityB = ::std::make_shared<::sdg::Entity>("B", "entity b"),
            entityC = ::std::make_shared<::sdg::Entity>("G", "entity c");

    ::std::shared_ptr<::sdg::Attribute>
            a_id_attribute,
            b_id_attribute;

    entityA->add_descriptor(a_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id", "A", ::sdg::Attribute::Scale::Ordinal)), true);
    entityB->add_descriptor(b_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("b_id", "B", ::sdg::Attribute::Scale::Ordinal)), true);
    entityB->add_descriptor(b_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("c_id", "C", ::sdg::Attribute::Scale::Nominal)), false);

    ::std::shared_ptr<::sdg::Relationship>
            C_A = make_shared<::sdg::Relationship>("c_to_a", entityC, entityA, false, ::sdg::Relationship::IDENTIFY_BY::LINK_1),
            C_B = make_shared<::sdg::Relationship>("c_to_b", entityC, entityB, false, ::sdg::Relationship::IDENTIFY_BY::LINK_1);

    model.add_thing(entityA);
    model.add_thing(entityB);
    model.add_thing(entityC);
    model.add_thing(C_A);
    model.add_thing(C_B);

    auto actualList = model.get_identifier_of_granular_entity();

    ASSERT_EQ(2, actualList.size());
}

TEST_F(MetadataTests, metadata_test_2 )
{
    ::sdg::Model model;

    ::std::shared_ptr<::sdg::Entity>
            entityA = ::std::make_shared<::sdg::Entity>("A", "entity a"),
            entityB = ::std::make_shared<::sdg::Entity>("B", "entity b"),
            entityC = ::std::make_shared<::sdg::Entity>("G", "entity c");

    ::std::shared_ptr<::sdg::Attribute>
            a_id_attribute,
            b_id_attribute;

    entityA->add_descriptor(a_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id", "A", ::sdg::Attribute::Scale::Ordinal)), true);
    entityB->add_descriptor(b_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("b_id", "B", ::sdg::Attribute::Scale::Ordinal)), true);
    entityB->add_descriptor(b_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("c_id", "C", ::sdg::Attribute::Scale::Nominal)), false);

    ::std::shared_ptr<::sdg::Relationship>
            C_A = make_shared<::sdg::Relationship>("c_to_a", entityC, entityA, false, ::sdg::Relationship::IDENTIFY_BY::LINK_1),
            C_B = make_shared<::sdg::Relationship>("c_to_b", entityC, entityB, false, ::sdg::Relationship::IDENTIFY_BY::LINK_1);

    model.add_thing(entityA);
    model.add_thing(entityB);
    model.add_thing(entityC);
    model.add_thing(C_A);
    model.add_thing(C_B);

    auto actualList = model.get_entity_identifier(::sdg::hash::EntityID("B"));

    ASSERT_EQ(1, actualList.size());
}

TEST_F(MetadataTests, metadata_test_3 )
{
    ::sdg::Model model;

    ::std::shared_ptr<::sdg::Entity>
            entityA = ::std::make_shared<::sdg::Entity>("A", "entity a"),
            entityB = ::std::make_shared<::sdg::Entity>("B", "entity b"),
            entityC = ::std::make_shared<::sdg::Entity>("G", "entity c");

    ::std::shared_ptr<::sdg::Attribute>
            a_id_attribute,
            b_id_attribute;

    entityA->add_descriptor(a_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("a_id", "A", ::sdg::Attribute::Scale::Ordinal)), true);
    entityB->add_descriptor(b_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("b_id", "B", ::sdg::Attribute::Scale::Ordinal)), true);
    entityB->add_descriptor(b_id_attribute=::std::make_shared<::sdg::Attribute>(::sdg::Attribute("c_id", "C", ::sdg::Attribute::Scale::Nominal)), false);

    ::std::shared_ptr<::sdg::Relationship>
            C_A = make_shared<::sdg::Relationship>("c_to_a", entityC, entityA, false, ::sdg::Relationship::IDENTIFY_BY::LINK_1),
            C_B = make_shared<::sdg::Relationship>("c_to_b", entityC, entityB, false, ::sdg::Relationship::IDENTIFY_BY::LINK_1);

    model.add_thing(entityA);
    model.add_thing(entityB);
    model.add_thing(entityC);
    model.add_thing(C_A);
    model.add_thing(C_B);

    auto found_descriptor = ::sdg::hash::DescriptorInstance("A", ::sdg::Attribute::Scale::Ordinal);
    found_descriptor.set_value(5);
    model.found_descriptor(found_descriptor);

    auto actualCount = model.get_entity_count(::sdg::hash::EntityID("A"));

    ASSERT_EQ(6, actualCount);
}
