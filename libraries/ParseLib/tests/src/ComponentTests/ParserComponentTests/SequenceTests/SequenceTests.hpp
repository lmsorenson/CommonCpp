#pragma once
#include "../Tests.hpp"
#include <memory>

#include "../../../../../src/abstract/parser/Parser.hpp"
#include "../../../../../src/abstract/parser/private/sequence/Sequence.hpp"
#include "TestTypes.hpp"

#include <gtest/gtest.h>

using sdg::parse::Sequence;

TEST_F(ParserComponentTests, parser_sequence_two_norepeat_tokens )
{
    sdg::Parser context;
    std::shared_ptr<Sequence> test_sequence = std::make_shared<Sequence>(&context, "root sequence");
    auto TokenTypeA = std::make_shared<TestTokenA>();
    auto TokenTypeB = std::make_shared<TestTokenB>();
    test_sequence->add_element(TokenTypeA);
    test_sequence->add_element(TokenTypeB);

    auto ResultA = test_sequence->match_token("A");
    auto ResultB = test_sequence->match_token("B");

    //assert that the results match the token that was expected.
    ASSERT_FALSE(std::dynamic_pointer_cast<TestTokenA>(ResultA) == nullptr);
    ASSERT_FALSE(std::dynamic_pointer_cast<TestTokenB>(ResultB) == nullptr);
}

TEST_F(ParserComponentTests, parser_sequence_with_unexpected_token )
{
    sdg::Parser context;
    std::shared_ptr<Sequence> test_sequence = std::make_shared<Sequence>(&context, "root sequence");
    auto TokenTypeA = std::make_shared<TestTokenA>();
    auto TokenTypeB = std::make_shared<TestTokenB>();
    test_sequence->add_element(TokenTypeA);
    test_sequence->add_element(TokenTypeB);


    auto ResultA = test_sequence->match_token("A");
    auto ResultB = test_sequence->match_token("B");
    //unexpected token
    auto ResultUnexpected = test_sequence->match_token("C");


    ASSERT_FALSE(std::dynamic_pointer_cast<TestTokenA>(ResultA) == nullptr);
    ASSERT_FALSE(std::dynamic_pointer_cast<TestTokenB>(ResultB) == nullptr);
    ASSERT_TRUE( ResultUnexpected == nullptr );
}

TEST_F(ParserComponentTests, parser_sequence_norepeat_subsequence_with_two_norepeat_tokens )
{
    sdg::Parser context;
    std::shared_ptr<Sequence> test_sequence = std::make_shared<Sequence>(&context, "root sequence");
    auto TokenTypeA = std::make_shared<TestTokenA>();
    auto TokenTypeB = std::make_shared<TestTokenB>();
    test_sequence->add_subsequence<TestTokenA, TestTokenB>(std::string("test_subsequence"), sdg::parse::SequenceElement::Cardinality::One, TokenTypeA, TokenTypeB);

    auto ResultA = test_sequence->match_token("A");
    auto ResultB = test_sequence->match_token("B");

    //assert that the results match the token that was expected.
    ASSERT_FALSE(std::dynamic_pointer_cast<TestTokenA>(ResultA) == nullptr);
    ASSERT_FALSE(std::dynamic_pointer_cast<TestTokenB>(ResultB) == nullptr);
}

TEST_F(ParserComponentTests, parser_sequence_norepeat_subsequence_with_unxpected_token )
{
    sdg::Parser context;
    std::shared_ptr<Sequence> test_sequence = std::make_shared<Sequence>(&context, "root sequence");
    auto TokenTypeA = std::make_shared<TestTokenA>();
    auto TokenTypeB = std::make_shared<TestTokenB>();
    test_sequence->add_subsequence<TestTokenA, TestTokenB>(std::string("test_subsequence"), sdg::parse::SequenceElement::Cardinality::One, TokenTypeA, TokenTypeB);

    auto ResultA = test_sequence->match_token("A");
    auto ResultB = test_sequence->match_token("B");
    auto ResultUnexpected = test_sequence->match_token("C");

    //assert that the results match the token that was expected.
    ASSERT_FALSE(std::dynamic_pointer_cast<TestTokenA>(ResultA) == nullptr);
    ASSERT_FALSE(std::dynamic_pointer_cast<TestTokenB>(ResultB) == nullptr);
    ASSERT_TRUE( ResultUnexpected == nullptr );
    
}