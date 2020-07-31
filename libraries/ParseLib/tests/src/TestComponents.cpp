#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "SetPath.hpp"

#include "ComponentTests/Manifest.hpp"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::sdg::SetPath(argc, argv);

    return RUN_ALL_TESTS();
}
