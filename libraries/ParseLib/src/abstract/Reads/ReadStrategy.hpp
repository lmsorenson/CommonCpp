// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include "ParserPipeline.hpp"
#include "../../../include/plDataSet.hpp"
#include "../../../include/ParseLib.hpp"


class ReadStrategy
{
    //ops
    virtual void configure_pipeline(ParserPipeline &pipeline) = 0;
    virtual int32_t set_read_options(std::vector<option> read_options)=0;

public:
    int32_t execute_read(const char * path, plDataSet &ds, std::vector<option> read_options);

    enum : int32_t
    {
        SUCCESS = 0,
        FILE_NOT_FOUND,
        FILE_FORMAT_INVALID,
        UNKNOWN_ERROR
    };
};