#pragma once
#include "../DataStructures/AbstractDataStructure.hpp"


class WriteStrategy
{
    // virtual void parse() = 0;
public:
    AbstractDataStructure run(const char * path);
};