// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ReadStrategy.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "../../utils/load_text.h"
#include <stdio.h> 
#include <time.h> 

using ::sdg::ReadStrategy;
using ::sdg::ParserPipeline;


    


int32_t ReadStrategy::execute_read(const char * filepath, sdg::DataSet &ds, std::vector<sdg::option> read_options)
{
    clock_t t; 
    double time_taken;


    t = clock(); 
    //load text
    // std::string raw_text;
    // if ((raw_text=utils::loadText(filepath))==LOAD_ERROR_STR)
    // {
    //     ds = sdg::DataSet(sdg::DataSet::DATA_SET_BAD);
    //     return FILE_NOT_FOUND;
    // }

    t = clock() - t; 
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    std::cout<<"time taken: "<<time_taken<<std::endl;
    
    t = clock(); 

    configure(file_loader_, character_queue_);
    configure_lexer( lexer_, token_queue_, character_queue_ );
    configure_parser( parser_, syntax_tree_, token_queue_ );
    configure_analyzer( semantic_analyzer_, &ds, syntax_tree_ );

    //set the read options before anything else
    this->set_read_options(read_options);
    

    if (file_loader_.load(filepath) == -1)
    {
        ds = sdg::DataSet(sdg::DataSet::DATA_SET_BAD);
        return FILE_NOT_FOUND;
    }

    syntax_tree_->Print();
    syntax_tree_->notify_observers();


    t = clock() - t; 
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    std::cout<<"time taken: "<<time_taken<<std::endl;

    
    t = clock(); 
    // std::shared_ptr<sdg::SyntaxNode> n = std::make_shared<sdg::SyntaxNode>(sdg::SyntaxNode(raw_text, nullptr));
    
    //decrypt
    
    //Configure pipeline
    ParserPipeline pipeline;
    this->configure_pipeline(pipeline);


    // int32_t err;
    // if( (err=pipeline.execute(n, ds)) )
    // {
    //     switch (err)
    //     {
    //         case ParserPipeline::PIPELINE_FORMAT_ERROR: 
    //         return FILE_FORMAT_INVALID; 
    //         break;

    //         default: return UNKNOWN_ERROR;
    //     }
    // }

    t = clock() - t; 
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    std::cout<<"time taken: "<<time_taken<<std::endl;

    return SUCCESS;
}