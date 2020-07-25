#pragma once
#include "../Tests.hpp"
#include <memory>

#include "../../../../../src/abstract/semantic_analyzer/SemanticAnalyzer.hpp"

#include <gtest/gtest.h>


TEST_F(SemanticAnalyzerComponentTests, add_item_no_precedent )
{
    ::sdg::SemanticNet net = ::sdg::SemanticNet();
    
    //pass in certain node properties.
    auto actual_item = net.add_item("token", ::sdg::NodeProperties("R", "root", 5));

    //assert that it produces a valid item of the correct type.
    ASSERT_NE(actual_item, nullptr);
}

TEST_F(SemanticAnalyzerComponentTests, add_item_matches_precedent )
{
    ::sdg::SemanticNet net = ::sdg::SemanticNet();

    //pass in certain node properties.
    net.add_item("token", ::sdg::NodeProperties("R", "root", 5));
    auto actual_item = net.add_item("token", ::sdg::NodeProperties("R", "root", 5));

    //assert that it produces a valid item of the correct type.
    ASSERT_NE(actual_item, nullptr);
}

TEST_F(SemanticAnalyzerComponentTests, add_item_does_not_match_precedent )
{
    ::sdg::SemanticNet net = ::sdg::SemanticNet();

    //pass in certain node properties.
    net.add_item("token", ::sdg::NodeProperties("R", "root", 4));
    auto actual_item = net.add_item("token", ::sdg::NodeProperties("R", "root", 5));

    //assert that it produces a valid item of the correct type.
    ASSERT_EQ(actual_item, nullptr);
}