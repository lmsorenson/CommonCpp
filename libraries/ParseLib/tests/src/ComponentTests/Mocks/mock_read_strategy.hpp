#pragma once
#include <gmock/gmock.h>
#include <objects/data_set.hpp>
#include <ReadStrategy.hpp>

class MockReadStrategy : public ::sdg::ReadStrategy
{
public:
    MockReadStrategy() = default;
    virtual ~MockReadStrategy() = default;

    MOCK_METHOD(void, configure_pipeline, (::sdg::ParserPipeline &pipeline), ());
    MOCK_METHOD(int32_t, set_read_options, (std::vector<sdg::option> read_options), ());

    MOCK_METHOD(void, configure, (::sdg::FileLoader &file_loader, ::sdg::pipeline::Stream<char> &character_stream), (const override));
    MOCK_METHOD(void, configure_lexer, (::sdg::Lexer &lexer, ::sdg::pipeline::Stream<std::string> &token_stream, ::sdg::pipeline::Stream<char> &character_stream, ::sdg::pipeline::Stream<Error> &error_queue_), (const override));
    MOCK_METHOD(void, configure_parser, (::sdg::Parser &parser, std::shared_ptr<::sdg::SyntaxNode> syntax_tree, ::sdg::pipeline::Stream<std::string> &token_stream, ::sdg::pipeline::Stream<Error> &error_queue_), (const override));
    MOCK_METHOD(void, configure_analyzer, (::sdg::SemanticAnalyzer &semantic_analyzer, ::sdg::DataSet *data_set, std::shared_ptr<::sdg::SyntaxNode> syntax_tree, ::sdg::pipeline::Stream<Error> &error_queue_), (const override));

    MOCK_METHOD(int32_t, execute_read, (const char * path, sdg::DataSet &ds, std::vector<sdg::option> read_options), (override));
};
