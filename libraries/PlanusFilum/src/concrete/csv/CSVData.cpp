// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSVData.hpp"
#include <iostream>
#include "../../colortext.hpp"


using namespace std;


CSVData::CSVData(int32_t hash_table_size)
: AbstractDataStructure(hash_table_size)
{
    cout << SetColor(CYAN, "constructing csv data . . . ") << endl;
}

CSVData::~CSVData()
{
    cout << SetColor(RED, "destructing csv data . . . ") << endl;
}

void CSVData::assign()
{
    cout << "assign csv data" << endl;
}