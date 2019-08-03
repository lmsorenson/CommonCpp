// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ReadStrategy.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "../../../include/loadText.h"



using namespace std;

int32_t ReadStrategy::execute_read(const char * filepath, AbstractDataStructure &ds)
{
    //load text
    string raw_text;
    if ((raw_text=loadText(filepath))==LOAD_ERROR_STR)
        return FILE_NOT_FOUND;

    shared_ptr<node> n = make_shared<node>(node(raw_text));
    
    //decrypt

    //Configure pipeline
    ParserPipeline pipeline;
    this->configure_pipeline(pipeline);
    pipeline.execute(n, ds);

    //parse text
    // vector<vector<string>> arr = parse(file_contents.c_str());

    //select fields
    // string sel = select();
    
    //assign fields
    // ds.assign();

    return 0;
}