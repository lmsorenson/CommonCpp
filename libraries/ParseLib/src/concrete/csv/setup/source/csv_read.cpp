// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../csv_read.hpp"

#include <iostream>

#include "../../HeaderShape.hpp"
#include "../../RecordShape.hpp"
#include "../../csv_filters.hpp"
#include "../../csv_token_filters.hpp"

using ::std::shared_ptr;
using ::std::vector;
using ::std::string;
using ::sdg::ParserPipeline;
using ::sdg::option;
using ::sdg::Lexer;
using ::sdg::csv::Read;
using ::sdg::SyntaxTreeTarget;

sdg::csv::Read::Read(){}
sdg::csv::Read::~Read(){}



void sdg::csv::Read::configure_pipeline(ParserPipeline &pipeline)
{
    if(this->b_use_header_line)
        pipeline.add_filter(shared_ptr<HeaderFilter> (new HeaderFilter("~H")));

    pipeline.add_filter(shared_ptr<RecordFilter> (new RecordFilter("R")));
    pipeline.add_filter(shared_ptr<FieldFilter> (new FieldFilter("F")));
    pipeline.add_output(shared_ptr<CSVOutput> (new CSVOutput()));
}

void Read::configure(FileLoader &file_loader, pipeline::Stream<char> &character_stream) const
{
    file_loader.set_target<CharacterTarget>( &character_stream );

}

void Read::configure_lexer(Lexer &lexer, pipeline::Stream<string> &token_stream, pipeline::Stream<char> &character_stream, pipeline::Stream<Error> &error_queue_) const
{
    //configures the lexer to listen for inputs on this character_stream.
    //and to send tokens to the following token stream.
    lexer.set_source<CharacterSource>( &character_stream );
    lexer.set_target<TokenTarget>( &token_stream );
    lexer.set_error_queue<ErrorQueue>( &error_queue_ );

    if (b_use_header_line)
        lexer.add_shape<HeaderShape>("H", Shape::Cardinality::One);

    lexer.add_shape<RecordShape>("R");
}

void Read::configure_parser(Parser &parser, shared_ptr<SyntaxNode> syntax_tree, pipeline::Stream<string> &token_stream, pipeline::Stream<Error> &error_queue_) const
{
    //configures the parser to listen for inputs on this token_stream.
    parser.set_source<TokenSource>( &token_stream );

    int32_t index =
    parser.add_token_type<RecordToken>("R");
    parser.add_token_type<FieldToken>("F", index);

    parser.set_error_queue<parser::ErrorQueue>( &error_queue_ );

    parser.set_target<SyntaxTreeTarget>( syntax_tree );
}

void Read::configure_analyzer(SemanticAnalyzer &semantic_analyzer, DataSet *data_set, std::shared_ptr<SyntaxNode> syntax_tree, pipeline::Stream<Error> &error_queue_) const
{
    semantic_analyzer.set_source<SyntaxTreeSource>(syntax_tree);

    semantic_analyzer.set_target<DataSetTarget>(data_set);
}

int32_t sdg::csv::Read::set_read_options(vector<option> read_options)
{
    for (auto option : read_options)
    {
        if((option.name == "header_line") && (option.value>0))
            this->b_use_header_line = true;
    }

    return 0;
}

