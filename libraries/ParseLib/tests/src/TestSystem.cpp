#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.hpp>

#include "SystemTests/CSV/Manifest.hpp"
#include "SetPath.hpp"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::sdg::SetPath(argc, argv);

	return RUN_ALL_TESTS();
}
