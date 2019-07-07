// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ReadCSV.hpp"
#include <iostream>
#include "../../../include/loadText.h"
#include "CSVFilters.hpp"

using namespace std;


ReadCSV::ReadCSV()
{
    cout << "constructing csv read strategy. . . " << endl;
}

ReadCSV::~ReadCSV()
{
    cout << "destructing csv read strategy. . . " << endl;
}



void ReadCSV::ConfigurePipeline(ParserPipeline &pipeline)
{
    cout << "configure csv pipeline: " << endl;
    pipeline.AddFilter(shared_ptr<RecordFilter> (new RecordFilter()));
    pipeline.AddFilter(shared_ptr<FieldFilter> (new FieldFilter()));
    pipeline.AddOutput(shared_ptr<CSVOutput> (new CSVOutput()));
}

vector<vector<string>> ReadCSV::parse(const char * file_contents)
{
    cout << "csv parse" << endl;

    vector<vector<string>> out;

    return out;
}


string ReadCSV::select()
{
    cout << "csv select" << endl;

    return "string";
}
