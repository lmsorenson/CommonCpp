#pragma once
#include "../Tests.hpp"
#include <memory>

#include "../../../../../src/abstract/semantic_analyzer/SemanticAnalyzer.hpp"

#include <gtest/gtest.h>


TEST_F(SemanticAnalyzerComponentTests, net_test1 )
{
    ::sdg::SemanticNet net = ::sdg::SemanticNet();
    
    //pass in certain node properties.
    net.add_item("token", ::sdg::NodeProperties());

    //assert that it produces a valid item of the correct type.
    ASSERT_EQ(1,2);
}