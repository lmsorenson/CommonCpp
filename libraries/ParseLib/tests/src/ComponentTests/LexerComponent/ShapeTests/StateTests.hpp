#pragma once
#include "../Tests.hpp"
#include <memory>

#include "../../../../../src/abstract/lexer/Lexer.hpp"
#include "../../../../../src/abstract/lexer/private/shape/LexerState.hpp"

#include <gtest/gtest.h>
#include "TestStates.hpp"
#include "TestShape.hpp"

using sdg::parse::Sequence;

TEST_F(LexerComponentTests, shape_run_character_satisfies_a_chain_of_transitions )
{
    Lexer lexer = Lexer();
    ShapeA shape(&lexer, ShapeA::Cardinality::One);
    shape.add_state<MockStateA>(1);
    shape.add_state<MockStateB>(2);
    shape.add_state<MockStateC>(3);
    auto mock_state_a = std::dynamic_pointer_cast<MockStateA>(shape.get_state<MockStateA>()).get();
    auto mock_state_b = std::dynamic_pointer_cast<MockStateB>(shape.get_state<MockStateB>()).get();
    auto mock_state_c = std::dynamic_pointer_cast<MockStateC>(shape.get_state<MockStateC>()).get();

    EXPECT_CALL(*mock_state_a, initialize('\0'))
    .Times(testing::Exactly(1));

    EXPECT_CALL(*mock_state_a, perform_scan('A'))
    .Times(testing::Exactly(1))
    .WillOnce(::testing::Return(StateTransition::SetStateB));

    EXPECT_CALL(*mock_state_b, perform_scan('A'))
    .Times(testing::Exactly(1))
    .WillOnce(::testing::Return(StateTransition::SetStateC));

    EXPECT_CALL(*mock_state_c, perform_scan('A'))
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
