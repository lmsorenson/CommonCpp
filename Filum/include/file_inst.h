#pragma once
#include <stdio.h>


class Filum
{
public:
    int32_t read_file(const char * filepath);
    int32_t write_file();
};