#pragma once
#include "../Tests.hpp"
#include <memory>

#include "../../../../../src/abstract/semantic_analyzer/SemanticAnalyzer.hpp"

#include <gtest/gtest.h>

TEST_F(SemanticAnalyzerComponentTests, net_test1 )
{
    ::sdg::SemanticNet net = ::sdg::SemanticNet();
    
    net.add_item("token", ::sdg::Properties());

    ASSERT_EQ(1,2);
}