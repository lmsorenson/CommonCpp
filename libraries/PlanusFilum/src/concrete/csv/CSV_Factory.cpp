// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSV_Factory.hpp"
#include "ReadCSV.hpp"
#include "CSVData.hpp"
#include <iostream>


using namespace std;

ReadStrategy * CSV_Factory::MakeRead()
{
    return new ReadCSV();
}

WriteStrategy * CSV_Factory::MakeWrite()
{
    return new WriteStrategy();
}

AbstractDataStructure * CSV_Factory::MakeData()
{
    return new CSVData();
}