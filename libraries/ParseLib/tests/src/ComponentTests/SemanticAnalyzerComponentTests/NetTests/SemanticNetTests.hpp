#pragma once
#include "../Tests.hpp"
#include <memory>

#include "../../../../../src/abstract/semantic_analyzer/SemanticAnalyzer.hpp"

#include <gtest/gtest.h>


TEST_F(SemanticAnalyzerComponentTests, add_item_no_precedent )
{
    ::std::vector<std::string> err;
    ::sdg::SemanticNet net = ::sdg::SemanticNet();
    
    //pass in certain node properties.
    auto actual_item = net.add_item(::sdg::NodeProperties("R", "root", 5), err);

    actual_item->print_line();

    //assert that it produces a valid item of the correct type.
    ASSERT_NE(actual_item, nullptr);
    ASSERT_EQ(actual_item->type(), ::sdg::ItemType::Record);
}

TEST_F(SemanticAnalyzerComponentTests, add_item_matches_precedent )
{
    ::std::vector<std::string> err;
    ::sdg::SemanticNet net = ::sdg::SemanticNet();

    //pass in certain node properties.
    net.add_item(::sdg::NodeProperties("R", "root", 5), err);
    auto actual_item = net.add_item(::sdg::NodeProperties("R", "root", 5), err);

    actual_item->print_line();

    //assert that it produces a valid item of the correct type.
    ASSERT_NE(actual_item, nullptr);
    ASSERT_EQ(actual_item->type(), ::sdg::ItemType::Record);
}

TEST_F(SemanticAnalyzerComponentTests, add_item_does_not_match_precedent )
{
    ::std::vector<std::string> err;
    ::sdg::SemanticNet net = ::sdg::SemanticNet();

    //pass in certain node properties.
    net.add_item(::sdg::NodeProperties("R", "root", 4), err);
    auto actual_item = net.add_item(::sdg::NodeProperties("R", "root", 5), err);

    //assert that it produces a valid item of the correct type.
    ASSERT_EQ(actual_item, nullptr);
}

TEST_F(SemanticAnalyzerComponentTests, add_item_matches_precedent_empty_payload )
{
    ::std::vector<std::string> err;
    ::sdg::SemanticNet net = ::sdg::SemanticNet();

    //pass in certain node properties.
    net.add_item(::sdg::NodeProperties("R", "root", 5), err);
    auto actual_item = net.add_item(::sdg::NodeProperties("R", "root", 5), err);

    actual_item->print_line();

    //assert that it produces a valid item of the correct type.
    ASSERT_NE(actual_item, nullptr);
    ASSERT_FALSE(actual_item->has_payload());
}

TEST_F(SemanticAnalyzerComponentTests, add_item_value_no_precedent )
{
    ::std::vector<std::string> err;
    ::sdg::SemanticNet net = ::sdg::SemanticNet();

    //pass in certain node properties.
    net.add_item(::sdg::NodeProperties("R", "root", 0), err);
    auto actual_item = net.add_item(::sdg::NodeProperties("F(aaa)", "R", 0), err);
    actual_item->print_line();

    //assert that it produces a valid item of the correct type.
    ASSERT_NE(actual_item, nullptr);
    ASSERT_EQ(actual_item->type(), ::sdg::ItemType::Value);
}

TEST_F(SemanticAnalyzerComponentTests, add_item_value_matches )
{
    ::std::vector<std::string> err;
    ::sdg::SemanticNet net = ::sdg::SemanticNet();

    //pass in certain node properties.
    net.add_item(::sdg::NodeProperties("R", "root", 5), err);
    auto actual_item = net.add_item(::sdg::NodeProperties("F(bbb)", "R", 0), err);
    actual_item->print_line();

    //assert that it produces a valid item of the correct type.
    ASSERT_NE(actual_item, nullptr);
    ASSERT_EQ(actual_item->type(), ::sdg::ItemType::Value);
}

TEST_F(SemanticAnalyzerComponentTests, add_item_value_does_not_match_regular_expression )
{
    ::std::vector<std::string> err;
    ::sdg::SemanticNet net = ::sdg::SemanticNet();

    //pass in certain node properties.
    net.add_item(::sdg::NodeProperties("R", "root", 4), err);
    auto actual_item = net.add_item(::sdg::NodeProperties("F", "R", 0), err);

    //assert that it produces a valid item of the correct type.
    ASSERT_EQ(actual_item, nullptr);
}

TEST_F(SemanticAnalyzerComponentTests, add_item_value_valid_payload )
{
    ::std::vector<std::string> err;
    ::sdg::SemanticNet net = ::sdg::SemanticNet();

    //pass in certain node properties.
    net.add_item(::sdg::NodeProperties("R", "root", 5), err);
    auto actual_item = net.add_item(::sdg::NodeProperties("F(bbb)", "R", 0), err);
    actual_item->print_line();

    //assert that it produces a valid item of the correct type.
    ASSERT_NE(actual_item, nullptr);
    ASSERT_TRUE(actual_item->has_payload());
}

TEST_F(SemanticAnalyzerComponentTests, add_item_header_no_precedent )
{
    ::std::vector<std::string> err;
    ::sdg::SemanticNet net = ::sdg::SemanticNet();

    //pass in certain node properties.
    auto actual_item = net.add_item(::sdg::NodeProperties("H", "root", 5), err);
    actual_item->print_line();

    //assert that it produces a valid item of the correct type.
    ASSERT_NE(actual_item, nullptr);
    ASSERT_EQ(actual_item->type(), ::sdg::ItemType::Header);
}

TEST_F(SemanticAnalyzerComponentTests, add_item_header_empty_payload )
{
    ::std::vector<std::string> err;
    ::sdg::SemanticNet net = ::sdg::SemanticNet();

    //pass in certain node properties.
    auto actual_item = net.add_item(::sdg::NodeProperties("H", "root", 5), err);
    actual_item->print_line();

    //assert that it produces a valid item of the correct type.
    ASSERT_NE(actual_item, nullptr);
    ASSERT_FALSE(actual_item->has_payload());
}