// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ReadStrategy.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "../../../include/loadText.h"



using namespace std;

int32_t ReadStrategy::execute_read(const char * filepath, plDataSet &ds)
{
    //load text
    string raw_text;
    if ((raw_text=loadText(filepath))==LOAD_ERROR_STR)
        return FILE_NOT_FOUND;

    shared_ptr<node> n = make_shared<node>(node(raw_text, nullptr));
    
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

    //parse text
    // vector<vector<string>> arr = parse(file_contents.c_str());

    //select fields
    // string sel = select();
    
    //assign fields
    // ds.assign();

    return SUCCESS;
}