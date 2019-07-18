// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSV_Factory.hpp"
#include "ReadCSV.hpp"
#include "CSVData.hpp"
#include <iostream>


using namespace std;

std::shared_ptr<ReadStrategy> CSV_Factory::make_read()
{
    return make_shared<ReadCSV>(ReadCSV());
}

std::shared_ptr<WriteStrategy> CSV_Factory::make_write()
{
    return make_shared<WriteStrategy>(WriteStrategy());
}

std::shared_ptr<AbstractDataStructure> CSV_Factory::make_data()
{
    return make_shared<CSVData>(CSVData(100));
}