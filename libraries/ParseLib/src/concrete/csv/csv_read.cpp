// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "csv_read.hpp"

#include <iostream>

#include "csv_filters.hpp"
#include "csv_token_filters.hpp"



using ::std::shared_ptr;
using ::std::deque;
using ::std::string;
using ::sdg::ParserPipeline;
using ::sdg::option;
using ::sdg::Lexer;
using ::sdg::csv::Read;

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

void Read::configure_lexer(Lexer &lexer, pipeline::Stream<string> &token_stream, pipeline::Stream<char> &character_stream) const
{
    //configures the lexer to listen for inputs on this character_stream.
    lexer.set_source<csv::CSVSource>( &character_stream );

    int32_t index = 
    lexer.add_filter<csv::RecordTokenFilter>( "R" );
    lexer.add_filter<csv::FieldTokenFilter>( "F", index );

    //configures the lexer to send tokens to the following token stream.
    lexer.set_target<csv::CSVTarget>( &token_stream );
}

void Read::configure_parser(Parser &parser, pipeline::Stream<string> &token_stream) const
{
    //configures the parser to listen for inputs on this token_stream.
    parser.set_source<csv::CSVTokenSource>( &token_stream );
}

int32_t sdg::csv::Read::set_read_options(std::vector<option> read_options)
{
    for (auto option : read_options)
    {
        if((option.name == "header_line") && (option.value>0))
            this->b_use_header_line = true;
    }

    return 0;
}

