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

int32_t ParserPipeline::AddOutput(shared_ptr<ParserOutput> output)
{
    this->output = output;
    return 0;
}

void ParserPipeline::execute(vector<string> text)
{
    cout << "executing pipeline. . . " << endl;
    cout << "number of filters: " << filters.size() << endl;
    
    vector<string> in_text_buffer;
    vector<string> out_text_buffer = text;
    

    //Execute filters
    for(int i=0; i < filters.size(); ++i)
    {
        //out text buffer from previous iteration becomes new in text buffer
        in_text_buffer = out_text_buffer;

        cout << "running filter: " << filters[i]->name() << endl;
        cout << "number of strings: " << in_text_buffer.size() << endl;
        
        //Apply filters to strings
        for (int k=0; k < in_text_buffer.size(); ++k)
        {
            out_text_buffer = filters[i]->execute(in_text_buffer[k].c_str());
        }
    }

    //message the output
    output->execute();
}