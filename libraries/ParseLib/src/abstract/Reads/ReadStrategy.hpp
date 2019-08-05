// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include "../DataStructures/InstanceSet.hpp"
#include "ParserPipeline.hpp"

class ReadStrategy
{
    virtual void configure_pipeline(ParserPipeline &pipeline) = 0;
    virtual std::vector<std::vector<std::string>> parse(const char * file_contents) = 0;
    virtual std::string select() = 0;

public:
    int32_t execute_read(const char * path, InstanceSet &ds);

    enum : int32_t
    {
        SUCCESS = 0,
        FILE_NOT_FOUND,
        FILE_FORMAT_INVALID,
        UNKNOWN_ERROR
    };
};