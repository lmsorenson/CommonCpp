// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ReadCSV.hpp"
#include <iostream>
#include "../../../include/loadText.h"
#include "../../colortext.hpp"
#include "CSVFilters.hpp"

using namespace std;


ReadCSV::ReadCSV()
{
    cout << SetColor(CYAN, "constructing csv read strategy. . . ") << '\r' << flush;
}

ReadCSV::~ReadCSV()
{
    cout << SetColor(RED, "destructing csv read strategy. . . ") << '\r' << flush;
}



void ReadCSV::configure_pipeline(ParserPipeline &pipeline)
{
    cout << "configure csv pipeline: " << '\r' << flush;
    pipeline.add_filter(shared_ptr<RecordFilter> (new RecordFilter("R")));
    pipeline.add_filter(shared_ptr<FieldFilter> (new FieldFilter("F")));
    pipeline.add_output(shared_ptr<CSVOutput> (new CSVOutput()));
}

vector<vector<string>> ReadCSV::parse(const char * file_contents)
{
    cout << "csv parse" << '\r' << flush;

    vector<vector<string>> out;

    return out;
}


string ReadCSV::select()
{
    cout << "csv select" << '\r' << flush;

    return "string";
}
