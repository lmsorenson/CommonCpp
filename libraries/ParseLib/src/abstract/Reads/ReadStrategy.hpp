// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>

#include <objects/data_set.hpp>
#include <ParseLib.hpp>

#include "Stream.hpp"

#include "../lexer/Lexer.hpp"
#include "../parser/Parser.hpp"
#include "ParserPipeline.hpp"


namespace sdg {

class ReadStrategy
{
    //ops
    virtual void configure_pipeline(ParserPipeline &pipeline) = 0;
    virtual void configure_lexer(Lexer &lexer, pipeline::Stream<std::string> &token_stream, pipeline::Stream<char> &character_stream) const =0;
    virtual void configure_parser(Parser &parser, pipeline::Stream<std::string> &token_stream) const =0;
    virtual int32_t set_read_options(std::vector<sdg::option> read_options)=0;

    Lexer lexer_;
    Parser parser_;


    pipeline::Stream<char> character_queue_;
    pipeline::Stream<std::string> token_queue_;
    
    //syntax_tree_

public:
    int32_t execute_read(const char * path, sdg::DataSet &ds, std::vector<sdg::option> read_options);

    enum : int32_t
    {
        SUCCESS = 0,
        FILE_NOT_FOUND,
        FILE_FORMAT_INVALID,
        UNKNOWN_ERROR
    };
};

}// namespace sdg
