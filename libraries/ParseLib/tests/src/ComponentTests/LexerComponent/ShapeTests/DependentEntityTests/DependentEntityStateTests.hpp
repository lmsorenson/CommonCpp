#pragma once
#include "../../Tests.hpp"
#include <memory>

#include "../../../../../../src/abstract/lexer/Lexer.hpp"
#include "../../../../../../src/abstract/lexer/public/DependentEntity.hpp"
#include "../../../../../../src/abstract/lexer/private/shape/dependent_entity/state/StartIndependentEntity.hpp"
#include "../../../../../../src/abstract/lexer/private/shape/dependent_entity/state/IndependentEntity.hpp"
#include "../../../../../../src/abstract/lexer/private/shape/dependent_entity/state/ScanningState.hpp"
#include "MockDependentEntity.hpp"

#include <gtest/gtest.h>

using sdg::parse::Sequence;
using sdg::dependent_entity::Scanning;
using sdg::StartIndependentEntity;
using std::string;
using ::testing::Exactly;

void create_buffer(MockLexer &lexer, string buffer)
{
    for(auto itr = buffer.begin(); itr != buffer.end(); itr++)
    {
        lexer.buffer(*itr);
    }
    
}

void dependent_run_helper(char ch, ::sdg::DependentEntity &mock_dependent, MockLexer &lexer)
{
    bool should_buffer;
    mock_dependent.run(should_buffer, ch);
    if(should_buffer)
        lexer.buffer(ch);
}

//input types
//-----------
//state
//lexer character buffer
//parent entity id
//cardinality
//character

TEST_F(LexerComponentTests, dependent_entity_run_initial_state_buffers_character )
{
    //---- input ---------------------------------
    string character_buffer = "";
    string parent_entity_id = "D";
    MockDependentEntity::Cardinality cardinality = MockDependentEntity::Cardinality::One;
    char character = 'z';

    //---- output --------------------------------
    bool expected_should_buffer = true;

    //---- setup ---------------------------------
    MockLexer mock_lexer = MockLexer();
    MockDependentEntity dependent_entity(&mock_lexer, "D", cardinality);
    auto mock_target = mock_lexer.get_mock_target();
    create_buffer(mock_lexer, character_buffer);
    dependent_entity.set_state<StartIndependentEntity>();

    //---- run -----------------------------------
    bool should_buffer;
    dependent_entity.run(should_buffer, character);

    //---- assert --------------------------------
    ASSERT_EQ(expected_should_buffer, should_buffer);
}

TEST_F(LexerComponentTests, dependent_entity_run_scanning_state_buffers_character )
{
    //---- input ---------------------------------
    string character_buffer = "";
    string parent_entity_id = "D";
    MockDependentEntity::Cardinality cardinality = MockDependentEntity::Cardinality::One;
    char character = 'z';

    //---- output --------------------------------
    bool expected_should_buffer = true;

    //---- setup ---------------------------------
    MockLexer mock_lexer = MockLexer();
    MockDependentEntity dependent_entity(&mock_lexer, "D", cardinality);
    auto mock_target = mock_lexer.get_mock_target();
    create_buffer(mock_lexer, character_buffer);
    dependent_entity.set_state<Scanning>();

    //---- run -----------------------------------
    bool should_buffer;
    dependent_entity.run(should_buffer, character);

    //---- assert --------------------------------
    ASSERT_EQ(expected_should_buffer, should_buffer);
}

TEST_F(LexerComponentTests, dependent_entity_run_item_delimiter_produces_token )
{
    //---- input ---------------------------------
    string character_buffer = "aa";
    string parent_entity_id = "D";
    MockDependentEntity::Cardinality cardinality = MockDependentEntity::Cardinality::One;
    char character = ',';

    //---- output --------------------------------
    string expected_token = "F(aa)";
    bool expected_should_buffer = false;

    //---- setup ---------------------------------
    MockLexer mock_lexer = MockLexer();
    MockDependentEntity dependent_entity(&mock_lexer, parent_entity_id, cardinality);
    auto mock_target = mock_lexer.get_mock_target();
    create_buffer(mock_lexer, character_buffer);
    dependent_entity.set_state<Scanning>();

    //---- assert --------------------------------
    EXPECT_CALL(*mock_target, send_token(expected_token)).Times(Exactly(1));

    //---- run -----------------------------------
    bool should_buffer;
    dependent_entity.run(should_buffer, character);

    //---- assert --------------------------------
    ASSERT_EQ(expected_should_buffer, should_buffer);
}


TEST_F(LexerComponentTests, dependent_entity_run_list_delimiter_produces_token )
{
    //---- input ---------------------------------
    string character_buffer = "bb";
    string parent_entity_id = "D";
    MockDependentEntity::Cardinality cardinality = MockDependentEntity::Cardinality::One;
    char character = '\r';

    //---- output --------------------------------
    string expected_token = "F(bb)";
    bool expected_should_buffer = false;

    //---- setup ---------------------------------
    MockLexer mock_lexer = MockLexer();
    MockDependentEntity dependent_entity(&mock_lexer, parent_entity_id, cardinality);
    auto mock_target = mock_lexer.get_mock_target();
    create_buffer(mock_lexer, character_buffer);
    dependent_entity.set_state<Scanning>();

    //---- assert --------------------------------
    EXPECT_CALL(*mock_target, send_token(expected_token)).Times(Exactly(1));

    //---- run -----------------------------------
    bool should_buffer;
    dependent_entity.run(should_buffer, character);

    //---- assert --------------------------------
    ASSERT_EQ(expected_should_buffer, should_buffer);
}


TEST_F(LexerComponentTests, dependent_entity_run )
{
    MockLexer lexer = MockLexer();
    MockDependentEntity mock_dependent(&lexer, "D", MockDependentEntity::Cardinality::One);

    auto mock_target = lexer.get_mock_target();

    EXPECT_CALL(*mock_target, send_token("D")).Times(::testing::Exactly(1));
    EXPECT_CALL(*mock_target, send_token("F(aa)")).Times(::testing::Exactly(1));
    EXPECT_CALL(*mock_target, send_token("F(bb)")).Times(::testing::Exactly(1));
    EXPECT_CALL(*mock_target, send_token("F(cc)")).Times(::testing::Exactly(1));

    dependent_run_helper('a', mock_dependent, lexer);
    dependent_run_helper('a', mock_dependent, lexer);
    dependent_run_helper(',', mock_dependent, lexer);
    dependent_run_helper('"', mock_dependent, lexer);
    dependent_run_helper('b', mock_dependent, lexer);
    dependent_run_helper('b', mock_dependent, lexer);
    dependent_run_helper('"', mock_dependent, lexer);
    dependent_run_helper(',', mock_dependent, lexer);
    dependent_run_helper('c', mock_dependent, lexer);
    dependent_run_helper('c', mock_dependent, lexer);
    dependent_run_helper('\r', mock_dependent, lexer);
    dependent_run_helper('\n', mock_dependent, lexer);
}
