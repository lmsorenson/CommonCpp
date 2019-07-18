// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSVData.hpp"
#include <iostream>
#include "../../colortext.hpp"


using namespace std;


CSVData::CSVData(int32_t hash_table_size)
: AbstractDataStructure(hash_table_size)
{
    cout << SetColor(CYAN, "constructing csv data . . . ") << '\r' << flush;
}

CSVData::~CSVData()
{
    cout << SetColor(RED, "destructing csv data . . . ") << '\r' << flush;
}

void CSVData::assign()
{
    cout << "assign csv data" << '\r' << flush;
}