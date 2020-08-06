#pragma once

#include "TestFramework.hpp"

namespace sdg {

void SetPath(int argc, char **argv)
{
    std::string path = argv[0];
    size_t position = path.find_last_of("/");
    if ( position != std::string::npos )
        LucTestFramework::SetPath(path.substr(0, position+1));
}

}// namespace sdg

