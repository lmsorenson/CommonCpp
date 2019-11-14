// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../DataStructures/plDataSet.hpp"
#include "../../../include/ParseLib.h"


class WriteStrategy
{
    // virtual void configure_pipeline(CompilerPipeline &pipeline) = 0;
    virtual int32_t set_read_options(std::vector<option> read_options)=0;

public:
    plDataSet execute_write(std::string path);

    enum : int32_t
    {
        SUCCESS = 0,
        UNKNOWN_ERROR
    };
};