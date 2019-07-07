// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ReadStrategy.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "../../../include/loadText.h"

using namespace std;

int32_t ReadStrategy::execute_read(const char * filepath, AbstractDataStructure &ds)
{
    cout << "Running read strategy." << endl; 

    //load text
    string file_contents = loadText(filepath);

    //decrypt

    //Configure pipeline
    ParserPipeline pipeline;
    this->ConfigurePipeline(pipeline);
    pipeline.execute(file_contents.c_str());

    //parse text
    // vector<vector<string>> arr = parse(file_contents.c_str());

    //select fields
    string sel = select();
    
    //assign fields
    ds.assign();

    return 0;
}