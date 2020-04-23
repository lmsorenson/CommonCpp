// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>

#include <objects/data_set.hpp>
#include <ParseLib.hpp>

#include "../lexer/Lexer.hpp"
#include "../parser/Parser.hpp"
#include "ParserPipeline.hpp"


namespace sdg {

class ReadStrategy
{
    //ops
    virtual void configure_pipeline(ParserPipeline &pipeline) = 0;
    virtual void configure_lexer(Lexer &lexer, std::deque<std::string> &token_stream)=0;
    virtual void configure_parser()=0;
    virtual int32_t set_read_options(std::vector<sdg::option> read_options)=0;

    Lexer lexer_;
    //Parser parser_

    std::deque<char> character_buffer_;
    std::deque<std::string> token_buffer_;
    
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
