// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "WriteStrategy.hpp"

#include <iostream>
#include <fstream>
#include "../Factories/AbstractFactory.hpp"
#include "../../../include/writeText.h"



using namespace std;

void WriteStrategy::execute_write(plDataSet dataset, std::string path)
{

    std::string out_str;

    //Configure pipeline
    ParserPipeline pipeline;
    this->configure_pipeline(pipeline);

    
    std::vector<std::vector<std::string>> vector_vector;

    for(int32_t i=0; i<dataset.size("R"); ++i)
    {
        std::string index = "R";
        index.append(std::to_string(i));

        vector_vector.push_back(dataset.get(index).get_vector());
    }

    int32_t err;
    if( (err=pipeline.inverse(vector_vector, out_str)) )
    {
        // switch (err)
        // {
        //     case ParserPipeline::PIPELINE_FORMAT_ERROR: 
        //     return FILE_FORMAT_INVALID; 
        //     break;

        //     default: return UNKNOWN_ERROR;
        // }
    }

    writeText(path, out_str);
}
