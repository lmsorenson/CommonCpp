// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ReadStrategy.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "../../utils/loadText.h"



using namespace std;

int32_t ReadStrategy::execute_read(const char * filepath, sdg::plDataSet &ds, std::vector<option> read_options)
{
    //load text
    string raw_text;
    if ((raw_text=loadText(filepath))==LOAD_ERROR_STR)
    {
        ds = sdg::plDataSet(sdg::plDataSet::DATA_SET_BAD);
        return FILE_NOT_FOUND;
    }
    
    //set the read options before anything else
    this->set_read_options(read_options);

    shared_ptr<plNode> n = make_shared<plNode>(plNode(raw_text, nullptr));
    
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