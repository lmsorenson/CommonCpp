// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ReadCSV.hpp"

#include <iostream>

#include "../../utils/loadText.h"
#include "CSVFilters.hpp"

using namespace std;


ReadCSV::ReadCSV(){}
ReadCSV::~ReadCSV(){}



void ReadCSV::configure_pipeline(ParserPipeline &pipeline)
{
    if(this->b_use_header_line)
        pipeline.add_filter(shared_ptr<HeaderFilter> (new HeaderFilter("~H")));

    pipeline.add_filter(shared_ptr<RecordFilter> (new RecordFilter("R")));
    pipeline.add_filter(shared_ptr<FieldFilter> (new FieldFilter("F")));
    pipeline.add_output(shared_ptr<CSVOutput> (new CSVOutput()));
}

int32_t ReadCSV::set_read_options(std::vector<sdg::option> read_options)
{
    for (auto option : read_options)
    {
        if((option.name == "header_line") && (option.value>0))
            this->b_use_header_line = true;
    }

    return 0;
}

