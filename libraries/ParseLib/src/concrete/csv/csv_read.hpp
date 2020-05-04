// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../../abstract/Reads/ReadStrategy.hpp"




namespace sdg {
namespace csv {

class Read : public ::sdg::ReadStrategy
{
    virtual void configure_pipeline( sdg::ParserPipeline &pipeline ) override;

    virtual void configure(FileLoader &file_loader, pipeline::Stream<char> &character_stream) const override;
    virtual void configure_lexer( Lexer &lexer, pipeline::Stream<std::string> &token_stream, pipeline::Stream<char> &character_stream ) const override;
    virtual void configure_parser( Parser &parser, std::shared_ptr<SyntaxNode> syntax_tree, pipeline::Stream<std::string> &token_stream ) const override;
    virtual void configure_analyzer(SemanticAnalyzer &semantic_analyzer, DataSet *data_set, std::shared_ptr<SyntaxNode> syntax_tree) const override;

    virtual int32_t set_read_options(std::vector<sdg::option> read_options) override;

    //csv read options
    bool b_use_header_line;

public:
    Read();
    ~Read();
};

}// namespace csv
}// namespace sdg