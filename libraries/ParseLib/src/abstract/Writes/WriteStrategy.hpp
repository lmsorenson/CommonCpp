// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <objects/data_set.hpp>
#include <ParseLib.hpp>
#include "../Reads/ParserPipeline.hpp"


namespace sdg {

class WriteStrategy
{
    virtual void configure_pipeline(sdg::ParserPipeline &pipeline) = 0;
    virtual int32_t set_write_options(std::vector<sdg::option> write_options)=0;
    virtual std::vector<std::vector<std::string>> get_dataset_contents(sdg::DataSet dataset)=0;

public:
    WriteStrategy() = default;
    virtual ~WriteStrategy() = default;

    int32_t execute_write(sdg::DataSet dataset, std::string path);

    enum : int32_t
    {
        SUCCESS = 0,
        UNKNOWN_ERROR
    };
};

}// namespace sdg