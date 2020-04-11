// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "WriteStrategy.hpp"

#include <iostream>
#include <fstream>
#include "../Factories/AbstractFactory.hpp"
#include "../../utils/writeText.h"


int32_t WriteStrategy::execute_write(sdg::DataSet dataset, std::string path)
{

    std::string out_str;

    //Configure pipeline
    ParserPipeline pipeline;
    this->configure_pipeline(pipeline);

    
    std::vector<std::vector<std::string>> vector_vector = get_dataset_contents(dataset);    

    int32_t err;
    if( (err=pipeline.inverse(vector_vector, out_str)) )
    {
        switch (err)
        {
            default: return UNKNOWN_ERROR;
        }
    }

    writeText(path, out_str);

    return 0;
}
