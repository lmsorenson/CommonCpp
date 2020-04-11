// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSV_Factory.hpp"

#include <iostream>

#include <formats/csv_data_set.hpp>
#include "ReadCSV.hpp"
#include "CSV_Write.hpp"

std::shared_ptr<sdg::ReadStrategy> CSV_Factory::make_read()
{
    return std::make_shared<ReadCSV>(ReadCSV());
}

std::shared_ptr<WriteStrategy> CSV_Factory::make_write()
{
    return std::make_shared<CSV_Write>(CSV_Write());
}

std::shared_ptr<sdg::DataSet> CSV_Factory::make_data()
{
    return std::make_shared<sdg::CSVData>(sdg::CSVData(100));
}