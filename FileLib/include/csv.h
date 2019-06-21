#pragma once
#include <stdio.h>
#include <string>
#include <vector>

typedef std::vector<std::vector<std::string>> CSV;

namespace file
{
    CSV loadCSV(const char * filepath);
}
