#pragma once
#include "../DataStructures/AbstractDataStructure.hpp"


class ReadStrategy
{
    virtual void parse() = 0;
    virtual void select() = 0;

public:
    AbstractDataStructure * run(const char * path);
};