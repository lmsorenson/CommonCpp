#pragma once
#include "../Tests.hpp"
#include <memory>

#include "../../../../../src/abstract/lexer/Lexer.hpp"
#include "Testitems.hpp"

#include <gtest/gtest.h>


TEST_F(LexerComponentTests, lexer_state_to_state_code )
{
     int32_t expected_code = 1;

    MockLexerStateA state(nullptr, expected_code);

    auto actual_code = state.to_state_code();

    ASSERT_EQ(expected_code, actual_code);
}

TEST_F(LexerComponentTests, lexer_state_occurances_prefix_increment )
{
    int32_t 
        expected_occurances_1 = 0,
        expected_occurances_2 = 1;

    MockLexerStateA state(nullptr, 1);

   
    int32_t actual_occurances;

    actual_occurances = state.occurances();
    ASSERT_EQ(expected_occurances_1, actual_occurances);
    
    ++state;
    actual_occurances = state.occurances();
    ASSERT_EQ(expected_occurances_2, actual_occurances);
}

TEST_F(LexerComponentTests, lexer_state_occurances_postfix_increment )
{
    int32_t 
        expected_occurances_1 = 0,
        expected_occurances_2 = 1;

    MockLexerStateA state(nullptr, 1);

   
    int32_t actual_occurances;

    actual_occurances = state.occurances();
    ASSERT_EQ(expected_occurances_1, actual_occurances);
    
    ++state;
    actual_occurances = state.occurances();
    ASSERT_EQ(expected_occurances_2, actual_occurances);
}
