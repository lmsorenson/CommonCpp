#pragma once
#include "../Tests.hpp"
#include <memory>

#include "../../../../../src/abstract/lexer/Lexer.hpp"
#include "../../../../../src/abstract/lexer/private/shape/LexerState.hpp"

#include <gtest/gtest.h>
#include "TestStates.hpp"
#include "TestShape.hpp"

using sdg::parse::Sequence;

TEST_F(LexerComponentTests, shape_run_ )
{
    Lexer lexer = Lexer();
    ShapeA shape(&lexer, ShapeA::Cardinality::One);
    shape.add_state<MockStateA>();
    auto mock_state_a = std::dynamic_pointer_cast<MockStateA>(shape.get_state<MockStateA>()).get();

    EXPECT_CALL(*mock_state_a, initialize('\0'))
    .Times(testing::Exactly(1));

    EXPECT_CALL(*mock_state_a, perform_scan('A'))
    .Times(testing::Exactly(1));

    bool should_buffer;
    shape.run(should_buffer, 'A');
}

TEST_F(LexerComponentTests, shape_run_with_no_states_does_not_fail )
{
    Lexer lexer = Lexer();
    ShapeA shape(&lexer, ShapeA::Cardinality::One);

    bool should_buffer;

    shape.run(should_buffer, 'A');
}
