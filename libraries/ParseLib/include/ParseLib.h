#pragma once
#include <stdio.h>
#include "../src/abstract/DataStructures/AbstractDataStructure.hpp"
#include <memory>


class ParseLib
{
public:
    int32_t read_file(AbstractDataStructure& data_store, const char * filepath);
    int32_t write_file();
};