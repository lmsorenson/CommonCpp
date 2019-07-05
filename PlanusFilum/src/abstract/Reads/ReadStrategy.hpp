#pragma once
#include <string>
#include <vector>
#include "../DataStructures/AbstractDataStructure.hpp"


class ReadStrategy
{
    virtual std::vector<std::vector<std::string>> parse(const char * file_contents) = 0;
    virtual std::string select() = 0;

public:
    AbstractDataStructure * Execute(const char * path);
};