// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ReadStrategy.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "../../utils/load_text.h"



using ::sdg::ReadStrategy;
using ::sdg::ParserPipeline;



int32_t ReadStrategy::execute_read(const char * filepath, sdg::DataSet &ds, std::vector<sdg::option> read_options)
{
    //load text
    std::string raw_text;
    if ((raw_text=utils::loadText(filepath))==LOAD_ERROR_STR)
    {
        ds = sdg::DataSet(sdg::DataSet::DATA_SET_BAD);
        return FILE_NOT_FOUND;
    }
    
    //set the read options before anything else
    this->set_read_options(read_options);

    std::shared_ptr<sdg::SyntaxNode> n = std::make_shared<sdg::SyntaxNode>(sdg::SyntaxNode(raw_text, nullptr));
    
    //decrypt
    

    //Configure pipeline
    ParserPipeline pipeline;
    this->configure_pipeline(pipeline);


    int32_t err;
    if( (err=pipeline.execute(n, ds)) )
    {
        switch (err)
        {
            case ParserPipeline::PIPELINE_FORMAT_ERROR: 
            return FILE_FORMAT_INVALID; 
            break;

            default: return UNKNOWN_ERROR;
        }
    }

    return SUCCESS;
}