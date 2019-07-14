// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSV_Factory.hpp"
#include "ReadCSV.hpp"
#include "CSVData.hpp"
#include <iostream>


using namespace std;

std::shared_ptr<ReadStrategy> CSV_Factory::MakeRead()
{
    return make_shared<ReadCSV>(ReadCSV());
}

std::shared_ptr<WriteStrategy> CSV_Factory::MakeWrite()
{
    return make_shared<WriteStrategy>(WriteStrategy());
}

std::shared_ptr<AbstractDataStructure> CSV_Factory::MakeData()
{
    return make_shared<CSVData>(CSVData(100));
}