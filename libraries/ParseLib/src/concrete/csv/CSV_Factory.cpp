// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSV_Factory.hpp"

#include <iostream>

#include "../../../include/concrete/CSVData.hpp"
#include "ReadCSV.hpp"
#include "CSV_Write.hpp"




using namespace std;

std::shared_ptr<ReadStrategy> CSV_Factory::make_read()
{
    return make_shared<ReadCSV>(ReadCSV());
}

std::shared_ptr<WriteStrategy> CSV_Factory::make_write()
{
    return make_shared<CSV_Write>(CSV_Write());
}

std::shared_ptr<sdg::plDataSet> CSV_Factory::make_data()
{
    return make_shared<CSVData>(CSVData(100));
}