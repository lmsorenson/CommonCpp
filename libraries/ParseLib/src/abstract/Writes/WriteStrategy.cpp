// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "WriteStrategy.hpp"

#include <iostream>
#include <fstream>
#include "../Factories/AbstractFactory.hpp"
#include "../../../include/writeText.h"



using namespace std;

plDataSet WriteStrategy::execute_write(std::string path)
{

    std::string out_str = "hello world";

    writeText(path, out_str);

    return plDataSet(100);
}
