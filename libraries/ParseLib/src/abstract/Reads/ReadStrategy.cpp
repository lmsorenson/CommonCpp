// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ReadStrategy.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "../../utils/load_text.h"
#include <stdio.h> 
#include <time.h> 

#include <formats/csv_data_set.hpp>
#include "../../utils/stopwatch.hpp"

using ::sdg::ReadStrategy;
using ::sdg::ParserPipeline;
using ::std::string;
using ::std::vector;
using ::std::make_shared;
using ::std::shared_ptr;
using ::std::cout;
using ::std::fixed;
using ::std::endl;

    


int32_t ReadStrategy::execute_read(const char * filepath, sdg::DataSet &ds, vector<sdg::option> read_options)
{
    clock_t t; 
    double time_taken;

    //set the read options before anything else
    this->set_read_options(read_options);

    configure(file_loader_, character_queue_);
    configure_lexer( lexer_, token_queue_, character_queue_, dead_letter_queue_ );
    configure_parser( parser_, syntax_tree_, token_queue_, dead_letter_queue_ );
    configure_analyzer( semantic_analyzer_, &ds, syntax_tree_, dead_letter_queue_ );

    t = clock(); 

    if (file_loader_.load(filepath) == -1)
    {
        ds = sdg::DataSet(sdg::DataSet::DATA_SET_BAD);
        return FILE_NOT_FOUND;
    }

    syntax_tree_->Print();
    syntax_tree_->notify_observers();


    cout<< fixed << "scan time taken: "<<lexer_.get_time()<<endl;
    cout<< fixed << "parse time taken: "<<parser_.get_time()<<endl;
    cout<< fixed <<"semantic analyzer time taken: "<<semantic_analyzer_.get_time()<<endl;
    cout<< fixed <<"data set target time taken: "<<semantic_analyzer_.get_target_time()<<endl;

    t = clock() - t; 
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    cout<< fixed <<"time taken: "<<time_taken<<endl;

    if (!dead_letter_queue_.is_empty())
    {
        auto err = dead_letter_queue_.get_element();

        //if there is an error return an empty.
        ds = sdg::DataSet(sdg::DataSet::DATA_SET_EMPTY);

        switch(err.code())
        {
            case 1: return FILE_FORMAT_INVALID;
            break;
            default: return UNKNOWN_ERROR; 
            break;
        }
    }


//    t = clock();
//    CSV test(100);

    // load text
//    string raw_text;
//    if ((raw_text=utils::loadText(filepath))==LOAD_ERROR_STR)
//    {
//        ds = sdg::DataSet(sdg::DataSet::DATA_SET_BAD);
//        return FILE_NOT_FOUND;
//    }
//
//    shared_ptr<sdg::SyntaxNode> n = make_shared<sdg::SyntaxNode>(sdg::SyntaxNode(raw_text, nullptr));
//
//    //decrypt
//
//    // Configure pipeline
//    ParserPipeline pipeline;
//    this->configure_pipeline(pipeline);
//
//
//    int32_t err;
//    if( (err=pipeline.execute(n, test)) )
//    {
//        switch (err)
//        {
//            case ParserPipeline::PIPELINE_FORMAT_ERROR:
//            return FILE_FORMAT_INVALID;
//            break;
//
//            default: return UNKNOWN_ERROR;
//        }
//    }
//
//    t = clock() - t;
//    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
//    cout<< fixed <<"time taken: "<<time_taken<<endl;

    return SUCCESS;
}