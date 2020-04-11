// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "csv_read.hpp"

#include <iostream>

#include "../../utils/loadText.h"
#include "csv_filters.hpp"


using ::std::shared_ptr;
using ::sdg::ParserPipeline;
using ::sdg::option;


sdg::csv::Read::Read(){}
sdg::csv::Read::~Read(){}



void sdg::csv::Read::configure_pipeline(ParserPipeline &pipeline)
{
    if(this->b_use_header_line)
        pipeline.add_filter(shared_ptr<HeaderFilter> (new HeaderFilter("~H")));

    pipeline.add_filter(shared_ptr<RecordFilter> (new RecordFilter("R")));
    pipeline.add_filter(shared_ptr<FieldFilter> (new FieldFilter("F")));
    pipeline.add_output(shared_ptr<CSVOutput> (new CSVOutput()));
}

int32_t sdg::csv::Read::set_read_options(std::vector<option> read_options)
{
    for (auto option : read_options)
    {
        if((option.name == "header_line") && (option.value>0))
            this->b_use_header_line = true;
    }

    return 0;
}

