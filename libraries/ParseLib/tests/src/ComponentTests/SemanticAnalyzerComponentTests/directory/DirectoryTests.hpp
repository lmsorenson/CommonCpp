#pragma once
#include "../Tests.hpp"
#include <memory>

#include "../../../../../src/abstract/semantic_analyzer/SemanticAnalyzer.hpp"

#include <gtest/gtest.h>

TEST_F(SemanticAnalyzerComponentTests, test1 )
{
    ::sdg::SemanticAnalyzer sa = ::sdg::SemanticAnalyzer();
    sa.get_time();

    ASSERT_EQ(1,2);
}