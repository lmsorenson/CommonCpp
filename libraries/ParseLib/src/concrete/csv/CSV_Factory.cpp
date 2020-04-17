// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "csv_factory.hpp"

#include <iostream>

#include <formats/csv_data_set.hpp>
#include "csv_read.hpp"
#include "csv_write.hpp"

std::shared_ptr<sdg::ReadStrategy> sdg::csv::Factory::make_read()
{
    return std::make_shared<Read>(Read());
}

std::shared_ptr<sdg::WriteStrategy> sdg::csv::Factory::make_write()
{
    return std::make_shared<Write>(Write());
}

std::shared_ptr<sdg::DataSet> sdg::csv::Factory::make_data()
{
    return std::make_shared<CSV>(CSV(100));
}