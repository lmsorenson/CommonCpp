// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <ParseLib.hpp>
#include <objects/data_set.hpp>

#include <iostream>
#include <string>

#include <formats/csv_data_set.hpp>
#include "abstract/Reads/ReadStrategy.hpp"
#include "concrete/csv/setup/csv_factory.hpp"

int32_t sdg::ParseLib::read_file(sdg::DataSet& data_store, const char * filepath, std::vector<sdg::option> read_options)
{

    //-----------------------|   Parse file path   |-----------------------//


    //-----------------------|   Generate strategies & Data   |-----------------------//
    csv::Factory factory;                    //TODO-->make factory producer
    auto data = factory.make_data();         //use the factory to initialize the data variable.
    auto strategy = factory.make_read();     //initialize appropriate read strategy

    //-----------------------|   Execute read   |-----------------------//
    int32_t return_code;
    if((return_code=strategy->execute_read(filepath, *data, read_options)))
    {
        switch (return_code)
        {
            case ReadStrategy::FILE_NOT_FOUND: 
                //assign the data store reference when returning out of the function.
                data_store = *data;
                return READ_FILE_NOT_FOUND; 
                break;
            case ReadStrategy::FILE_FORMAT_INVALID: 
                //assign the data store reference when returning out of the function.
                data_store = *data;
                return READ_FORMAT_INVALID; 
                break;
            default: return UNKNOWN_ERROR; break;
        }
    }

    //-----------------------|   Clean up   |-----------------------//

    //-----------------------|   Return   |-----------------------//
    data_store = *data;
    return READ_SUCCESSFUL;
}

int32_t sdg::ParseLib::write_file(sdg::DataSet& data_store, const char * filepath, std::vector<sdg::option> read_options)
{
    //-----------------------|   Generate strategies & Data   |-----------------------//
    csv::Factory factory;                    //TODO-->make factory producer
    auto strategy = factory.make_write();     //initialize appropriate read strategy
    strategy->execute_write(data_store, filepath);

    return 0;
}

