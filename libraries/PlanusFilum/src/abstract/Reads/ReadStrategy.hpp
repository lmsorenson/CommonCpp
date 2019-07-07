// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include "../DataStructures/AbstractDataStructure.hpp"
#include "ParserPipeline.hpp"

class ReadStrategy
{
    virtual void ConfigurePipeline(ParserPipeline &pipeline) = 0;
    virtual std::vector<std::vector<std::string>> parse(const char * file_contents) = 0;
    virtual std::string select() = 0;

public:
    int32_t execute_read(const char * path, AbstractDataStructure &ds);
};