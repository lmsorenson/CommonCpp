#pragma once
#include "../../Tests.hpp"
#include <memory>

#include "../../../../../../src/abstract/lexer/Lexer.hpp"
#include "../../../../../../src/abstract/lexer/public/DependentEntity.hpp"
#include "MockDependentEntity.hpp"

#include <gtest/gtest.h>

using sdg::parse::Sequence;

void dependent_run_helper(char ch, ::sdg::DependentEntity &mock_dependent, MockLexer &lexer)
{
    bool should_buffer;
    mock_dependent.run(should_buffer, ch);
    if(should_buffer)
        lexer.buffer(ch);
}

TEST_F(LexerComponentTests, dependent_state_test_1 )
{
    MockLexer lexer = MockLexer();
    MockDependentEntity mock_dependent(&lexer, "D", MockDependentEntity::Cardinality::One);

    auto mock_target = lexer.get_mock_target();

    EXPECT_CALL(*mock_target, send_token("D")).Times(::testing::Exactly(1));
    EXPECT_CALL(*mock_target, send_token("F(aa)")).Times(::testing::Exactly(1));

    dependent_run_helper('a', mock_dependent, lexer);
    dependent_run_helper('a', mock_dependent, lexer);
    dependent_run_helper(',', mock_dependent, lexer);
    dependent_run_helper('b', mock_dependent, lexer);
    dependent_run_helper('b', mock_dependent, lexer);
}
