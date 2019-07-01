#pragma once
#include <string>
#include <vector>
#include "../DataStructures/AbstractDataStructure.hpp"


class ReadStrategy
{
    virtual std::vector<std::string> parse() = 0;
    virtual std::string select() = 0;

public:
    AbstractDataStructure * run(const char * path);
};