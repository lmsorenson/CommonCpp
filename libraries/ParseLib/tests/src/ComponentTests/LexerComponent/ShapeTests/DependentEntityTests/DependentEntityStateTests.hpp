#pragma once
#include "../../Tests.hpp"
#include <memory>

#include "../../../../../../src/abstract/lexer/Lexer.hpp"
#include "../../../../../../src/abstract/lexer/public/DependentEntity.hpp"
#include "../../../../../../src/abstract/lexer/private/shape/dependent_entity/state/StartIndependentEntity.hpp"
#include "../../../../../../src/abstract/lexer/private/shape/dependent_entity/state/IndependentEntity.hpp"
#include "../../../../../../src/abstract/lexer/private/shape/dependent_entity/state/ScanningState.hpp"
#include "../../../../../../src/abstract/lexer/private/shape/dependent_entity/state/EscapedState.hpp"
#include "../../../../../../src/abstract/lexer/private/shape/dependent_entity/state/FoundState.hpp"
#include "../../../../../../src/abstract/lexer/private/shape/dependent_entity/state/PendingState.hpp"
#include "../../../../../../src/abstract/lexer/private/shape/dependent_entity/state/AllowEscapeCharacter.hpp"
#include "../../../../../../src/abstract/lexer/private/shape/dependent_entity/state/DelimiterFoundState.hpp"
#include "MockDependentEntity.hpp"
#include "../../../../../../src/abstract/intermediate/Error.hpp"

#include <gtest/gtest.h>

using sdg::dependent_entity::Scanning;
using sdg::dependent_entity::ScanningEscaped;
using sdg::dependent_entity::FoundDependent;
using sdg::dependent_entity::DelimiterFound;
using sdg::PendingState;
using sdg::dependent_entity::AllowEscapeCharacter;
using sdg::StartIndependentEntity;
using std::string;
using ::testing::Exactly;
using ::testing::_;

//------------ Helpers -----------------
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

TEST_F(LexerComponentTests, lexer_dependent_entity_run_initial_state_to_scanning_state )
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
    ASSERT_TRUE(dependent_entity.state_equals<Scanning>());
}

TEST_F(LexerComponentTests, lexer_dependent_entity_run_initial_state_to_scanning_escaped_state )
{
    //---- input ---------------------------------
    string character_buffer = "";
    string parent_entity_id = "D";
    MockDependentEntity::Cardinality cardinality = MockDependentEntity::Cardinality::One;
    char character = '\"';

    //---- output --------------------------------
    bool expected_should_buffer = false;

    //---- setup ---------------------------------
    MockLexer mock_lexer = MockLexer();
    MockDependentEntity dependent_entity(&mock_lexer, "D", cardinality);
    auto mock_target = mock_lexer.get_mock_target();
    create_buffer(mock_lexer, character_buffer);
    dependent_entity.set_state<StartIndependentEntity>();

    //---- assert --------------------------------
    EXPECT_CALL(*mock_target, send_token(parent_entity_id)).Times(Exactly(1));

    //---- run -----------------------------------
    bool should_buffer;
    dependent_entity.run(should_buffer, character);

    //---- assert --------------------------------
    ASSERT_EQ(expected_should_buffer, should_buffer);
    ASSERT_TRUE(dependent_entity.state_equals<ScanningEscaped>());
}

TEST_F(LexerComponentTests, lexer_dependent_entity_run_escaped_state_to_delimiter_found )
{
    //---- input ---------------------------------
    string parent_entity_id = "D";
    MockDependentEntity::Cardinality cardinality = MockDependentEntity::Cardinality::One;
    char character = '"';

    //---- output --------------------------------
    bool expected_should_buffer = false;

    //---- setup ---------------------------------
    MockLexer mock_lexer = MockLexer();
    MockDependentEntity dependent_entity(&mock_lexer, "D", cardinality);
    auto mock_target = mock_lexer.get_mock_target();
    dependent_entity.set_state<Scanning>();

    //---- run -----------------------------------
    bool should_buffer;
    dependent_entity.run(should_buffer, '\"');
    dependent_entity.run(should_buffer, 'a');
    dependent_entity.run(should_buffer, character);

    //---- assert --------------------------------
    ASSERT_EQ(expected_should_buffer, should_buffer);
    ASSERT_TRUE(dependent_entity.state_equals<DelimiterFound>());
}

TEST_F(LexerComponentTests, lexer_dependent_entity_run_escaped_state_through_delimiter_found_to_scanning_state )
{
    //---- input ---------------------------------
    string character_buffer = "bbb";
    string parent_entity_id = "D";
    MockDependentEntity::Cardinality cardinality = MockDependentEntity::Cardinality::One;

    //---- output --------------------------------
    bool expected_should_buffer = false;

    //---- setup ---------------------------------
    MockLexer mock_lexer = MockLexer();
    MockDependentEntity dependent_entity(&mock_lexer, parent_entity_id, cardinality);
    auto mock_target = mock_lexer.get_mock_target();
    create_buffer(mock_lexer, character_buffer);
    dependent_entity.set_state<Scanning>();

    //---- run -----------------------------------
    bool actual_should_buffer;
    dependent_entity.run(actual_should_buffer, '\"');
    dependent_entity.run(actual_should_buffer, 'a');
    dependent_entity.run(actual_should_buffer, '\"');
    ASSERT_EQ(expected_should_buffer, actual_should_buffer);

    dependent_entity.run(actual_should_buffer, 'a');//transition goes through AllowEscapeCharacter state
    
    //---- assert --------------------------------
    ASSERT_EQ(true, actual_should_buffer);
    ASSERT_TRUE(dependent_entity.state_equals<Scanning>());
}

TEST_F(LexerComponentTests, lexer_dependent_entity_run_allow_escape_characters_buffers_escape_character )
{
    //---- input ---------------------------------
    string character_buffer = "bbb";
    string parent_entity_id = "D";
    MockDependentEntity::Cardinality cardinality = MockDependentEntity::Cardinality::One;

    //---- setup ---------------------------------
    MockLexer mock_lexer = MockLexer();
    MockDependentEntity dependent_entity(&mock_lexer, parent_entity_id, cardinality);
    auto mock_target = mock_lexer.get_mock_target();
    create_buffer(mock_lexer, character_buffer);
    dependent_entity.set_state<Scanning>();

    //---- run -----------------------------------
    bool should_buffer;
    dependent_entity.run(should_buffer, '\"');
    dependent_entity.run(should_buffer, 'a');
    dependent_entity.run(should_buffer, '\"');
    ASSERT_EQ(false, should_buffer);

    dependent_entity.run(should_buffer, '\"');
    ASSERT_EQ(true, should_buffer);
    dependent_entity.run(should_buffer, 'a');
    
    //---- assert --------------------------------
    ASSERT_EQ(true, should_buffer);
    ASSERT_TRUE(dependent_entity.state_equals<ScanningEscaped>());
}

TEST_F(LexerComponentTests, lexer_dependent_entity_run_escaped_state_no_transition_buffers_character )
{
    //---- input ---------------------------------
    string character_buffer = "";
    string parent_entity_id = "D";
    MockDependentEntity::Cardinality cardinality = MockDependentEntity::Cardinality::One;
    char character = '\r';

    //---- output --------------------------------
    bool expected_should_buffer = true;

    //---- setup ---------------------------------
    MockLexer mock_lexer = MockLexer();
    MockDependentEntity dependent_entity(&mock_lexer, "D", cardinality);
    auto mock_target = mock_lexer.get_mock_target();
    create_buffer(mock_lexer, character_buffer);
    dependent_entity.set_state<ScanningEscaped>();

    //---- run -----------------------------------
    bool should_buffer;
    dependent_entity.run(should_buffer, character);

    //---- assert --------------------------------
    ASSERT_EQ(expected_should_buffer, should_buffer);
    ASSERT_TRUE(dependent_entity.state_equals<ScanningEscaped>());
}

TEST_F(LexerComponentTests, lexer_dependent_entity_run_scanning_state_no_transition_buffers_character )
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
    ASSERT_TRUE(dependent_entity.state_equals<Scanning>());
}

TEST_F(LexerComponentTests, lexer_dependent_entity_run_item_delimiter_produces_token )
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

TEST_F(LexerComponentTests, lexer_dependent_entity_run_empty_token_sends_error )
{
    //---- input ---------------------------------
    string character_buffer = "";
    string parent_entity_id = "D";
    MockDependentEntity::Cardinality cardinality = MockDependentEntity::Cardinality::One;
    char character = '\r';

    //---- output --------------------------------
    bool expected_should_buffer = false;

    //---- setup ---------------------------------
    MockLexer mock_lexer = MockLexer();
    MockDependentEntity dependent_entity(&mock_lexer, parent_entity_id, cardinality);
    auto mock_error_queue = mock_lexer.get_mock_error_queue();
    create_buffer(mock_lexer, character_buffer);
    dependent_entity.set_state<FoundDependent>();

    //---- assert --------------------------------
    EXPECT_CALL(*mock_error_queue, add_error(_)).Times(Exactly(1));

    //---- run -----------------------------------
    bool should_buffer;
    dependent_entity.run(should_buffer, character);

    //---- assert --------------------------------
    ASSERT_EQ(expected_should_buffer, should_buffer);
}

TEST_F(LexerComponentTests, lexer_dependent_entity_run_list_delimiter_produces_token )
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

TEST_F(LexerComponentTests, lexer_dependent_entity_run )
{
    MockLexer lexer = MockLexer();
    MockDependentEntity mock_dependent(&lexer, "D", MockDependentEntity::Cardinality::One);

    auto mock_target = lexer.get_mock_target();

    EXPECT_CALL(*mock_target, send_token("D")).Times(Exactly(1));
    EXPECT_CALL(*mock_target, send_token("F(aa)")).Times(Exactly(1));
    EXPECT_CALL(*mock_target, send_token("F(bb\r)")).Times(Exactly(1));
    EXPECT_CALL(*mock_target, send_token("F(cc)")).Times(Exactly(1));

    dependent_run_helper('a', mock_dependent, lexer);
    dependent_run_helper('a', mock_dependent, lexer);
    dependent_run_helper(',', mock_dependent, lexer);
    dependent_run_helper('"', mock_dependent, lexer);
    dependent_run_helper('b', mock_dependent, lexer);
    dependent_run_helper('b', mock_dependent, lexer);
    dependent_run_helper('\r', mock_dependent, lexer);
    dependent_run_helper('"', mock_dependent, lexer);
    dependent_run_helper(',', mock_dependent, lexer);
    dependent_run_helper('c', mock_dependent, lexer);
    dependent_run_helper('c', mock_dependent, lexer);
    dependent_run_helper('\r', mock_dependent, lexer);
    dependent_run_helper('\n', mock_dependent, lexer);
}

TEST_F(LexerComponentTests, lexer_dependent_entity_run_alternate )
{
    MockLexer lexer = MockLexer();
    MockDependentEntityB mock_dependent(&lexer, "D", MockDependentEntity::Cardinality::One);

    auto mock_target = lexer.get_mock_target();

    EXPECT_CALL(*mock_target, send_token("D")).Times(Exactly(1));
    EXPECT_CALL(*mock_target, send_token("F(aa)")).Times(Exactly(1));
    EXPECT_CALL(*mock_target, send_token("F(b|b)")).Times(Exactly(1));
    EXPECT_CALL(*mock_target, send_token("F(cc)")).Times(Exactly(1));


    dependent_run_helper('a', mock_dependent, lexer);
    dependent_run_helper('a', mock_dependent, lexer);
    dependent_run_helper('|', mock_dependent, lexer);
    dependent_run_helper('b', mock_dependent, lexer);
    dependent_run_helper('(', mock_dependent, lexer);
    dependent_run_helper('|', mock_dependent, lexer);
    dependent_run_helper(')', mock_dependent, lexer);
    dependent_run_helper('b', mock_dependent, lexer);
    dependent_run_helper('|', mock_dependent, lexer);
    dependent_run_helper('c', mock_dependent, lexer);
    dependent_run_helper('c', mock_dependent, lexer);
    dependent_run_helper('}', mock_dependent, lexer);
}

TEST_F(LexerComponentTests, lexer_dependent_entity_run_with_quote_in_field )
{
    MockLexer lexer = MockLexer();
    MockDependentEntity mock_dependent(&lexer, "D", MockDependentEntity::Cardinality::One);

    auto mock_target = lexer.get_mock_target();

    EXPECT_CALL(*mock_target, send_token("D")).Times(Exactly(1));
    EXPECT_CALL(*mock_target, send_token("F(aa)")).Times(Exactly(1));
    EXPECT_CALL(*mock_target, send_token("F(b\"b\r)")).Times(Exactly(1));
    EXPECT_CALL(*mock_target, send_token("F(cc)")).Times(Exactly(1));

    dependent_run_helper('a', mock_dependent, lexer);
    dependent_run_helper('a', mock_dependent, lexer);
    dependent_run_helper(',', mock_dependent, lexer);
    dependent_run_helper('"', mock_dependent, lexer);
    dependent_run_helper('b', mock_dependent, lexer);
    dependent_run_helper('"', mock_dependent, lexer);
    dependent_run_helper('"', mock_dependent, lexer);
    dependent_run_helper('b', mock_dependent, lexer);
    dependent_run_helper('\r', mock_dependent, lexer);
    dependent_run_helper('"', mock_dependent, lexer);
    dependent_run_helper(',', mock_dependent, lexer);
    dependent_run_helper('c', mock_dependent, lexer);
    dependent_run_helper('c', mock_dependent, lexer);
    dependent_run_helper('\r', mock_dependent, lexer);
    dependent_run_helper('\n', mock_dependent, lexer);
}