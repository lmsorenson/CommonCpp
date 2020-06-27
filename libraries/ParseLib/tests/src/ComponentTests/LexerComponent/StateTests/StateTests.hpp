#pragma once
#include "../Tests.hpp"
#include <memory>

#include "../../../../../src/abstract/parser/Parser.hpp"
#include "../../../../../src/abstract/parser/private/sequence/Sequence.hpp"

#include <gtest/gtest.h>

using sdg::parse::Sequence;

TEST_F(LexerComponentTests, state_test_1 )
{
    //assert that the results match the token that was expected.
    ASSERT_EQ(1,2);
}
