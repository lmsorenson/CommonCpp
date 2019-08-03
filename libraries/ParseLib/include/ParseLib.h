#pragma once
#include <stdio.h>
#include "../src/abstract/DataStructures/AbstractDataStructure.hpp"
#include <memory>


class ParseLib
{
public:
    int32_t read_file(AbstractDataStructure& data_store, const char * filepath);
    int32_t write_file();

    //READ CODES
    enum : int32_t
    {
        READ_SUCCESSFUL,
        READ_FORMAT_INVALID,
        READ_FILE_NOT_FOUND,
        WRITE_SUCCESSFUL,
        UNKNOWN_ERROR
    };
};