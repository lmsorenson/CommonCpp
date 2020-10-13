// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <ParseLib.hpp>
#include <objects/data_set.hpp>

#include <iostream>
#include <string>
#include <memory>

#include <formats/csv_data_set.hpp>
#include "abstract/Factories/AbstractFactory.hpp"
#include "abstract/Reads/ReadStrategy.hpp"
#include "concrete/csv/setup/csv_factory.hpp"

using ::sdg::ParseLib;
using ::sdg::AbstractFactory;
using ::sdg::ReadStrategy;
using ::sdg::WriteStrategy;
using ::std::make_unique;
using ::std::unique_ptr;

unique_ptr<AbstractFactory> ParseLib::produce_factory()
{
    return make_unique<csv::Factory>();
}

int32_t ParseLib::read_file(sdg::DataSet& data_store, const char * filepath, std::vector<sdg::option> read_options)
{
    //-----------------------|   Generate strategies & Data   |-----------------------//
    factory_ = this->produce_factory();
    auto data = factory_->make_data();         //use the factory to initialize the data variable.
    auto strategy = factory_->make_read();     //initialize appropriate read strategy

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
    factory_ = nullptr;

    //-----------------------|   Return   |-----------------------//
    data_store = *data;
    return READ_SUCCESSFUL;
}

int32_t ParseLib::write_file(sdg::DataSet& data_store, const char * filepath, std::vector<sdg::option> read_options)
{
    //-----------------------|   Generate strategies & Data   |-----------------------//
    factory_ = this->produce_factory();
    auto strategy = factory_->make_write();     //initialize appropriate read strategy
    strategy->execute_write(data_store, filepath);

    //-----------------------|   Clean up   |-----------------------//
    factory_ = nullptr;

    //-----------------------|   Return   |-----------------------//
    return WRITE_SUCCESSFUL;
}

