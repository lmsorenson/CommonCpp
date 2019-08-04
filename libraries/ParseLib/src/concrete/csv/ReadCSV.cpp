// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ReadCSV.hpp"
#include <iostream>
#include "../../../include/loadText.h"
#include "../../colortext.hpp"
#include "CSVFilters.hpp"

using namespace std;


ReadCSV::ReadCSV(){}
ReadCSV::~ReadCSV(){}



void ReadCSV::configure_pipeline(ParserPipeline &pipeline)
{
    pipeline.add_filter(shared_ptr<RecordFilter> (new RecordFilter("R")));
    pipeline.add_filter(shared_ptr<FieldFilter> (new FieldFilter("F")));
    pipeline.add_output(shared_ptr<CSVOutput> (new CSVOutput()));
}

vector<vector<string>> ReadCSV::parse(const char * file_contents)
{
    vector<vector<string>> out;
    return out;
}


string ReadCSV::select()
{
    return "string";
}
