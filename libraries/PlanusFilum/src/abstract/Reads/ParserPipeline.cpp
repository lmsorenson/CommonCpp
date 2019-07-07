// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ParserPipeline.hpp"
#include <iostream>
#include <vector>


using namespace std;

ParserPipeline::ParserPipeline(){}
ParserPipeline::~ParserPipeline()
{
    cout << "deconstructing parser pipeline. . ." << endl;

}

int32_t ParserPipeline::AddFilter(shared_ptr<ParserFilter> filter)
{
    filters.push_back(filter);
    return 0;
}

void ParserPipeline::execute(vector<string> text)
{
    cout << "executing pipeline. . . " << endl;
    cout << "number of filters: " << filters.size() << endl;
    //Execute filters
    for(int i=0; i < filters.size(); ++i)
    {
        cout << "running filter: " << filters[i]->name() << endl;
        cout << "number of strings: " << text.size() << endl;
        //Apply filters to strings
        for (int k=0; k < text.size(); ++k)
        {
            filters[i]->execute(text[k].c_str());
        }
    }

    //message the output
}