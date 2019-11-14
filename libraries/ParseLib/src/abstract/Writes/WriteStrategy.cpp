// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "WriteStrategy.hpp"

#include <iostream>
#include <fstream>
#include "../Factories/AbstractFactory.hpp"
#include "../../../include/writeText.h"



using namespace std;

void WriteStrategy::execute_write(plDataSet dataset, std::string path)
{

    std::string out_str;



    writeText(path, out_str);
}
