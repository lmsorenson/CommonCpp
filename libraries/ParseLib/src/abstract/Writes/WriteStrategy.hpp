// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../../include/plDataSet.hpp"
#include "../../../include/ParseLib.hpp"
#include "../Reads/ParserPipeline.hpp"


class WriteStrategy
{
    virtual void configure_pipeline(ParserPipeline &pipeline) = 0;
    virtual int32_t set_write_options(std::vector<option> write_options)=0;
    virtual std::vector<std::vector<std::string>> get_dataset_contents(plDataSet dataset)=0;

public:
    int32_t execute_write(plDataSet dataset, std::string path);

    enum : int32_t
    {
        SUCCESS = 0,
        UNKNOWN_ERROR
    };
};