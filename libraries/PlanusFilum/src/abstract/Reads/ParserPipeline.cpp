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

void ParserPipeline::execute(vector<node> text)
{
    cout << "executing pipeline. . . " << endl;
    cout << "number of filters: " << filters.size() << endl;
    
    vector<shared_ptr<vector<node>>> in_buffer;
    vector<shared_ptr<vector<node>>> out_buffer;

    //make a copy of the input
    vector<node> copy = text;
    //
    out_buffer.push_back(make_shared<vector<node>>(copy));

    //for loops
    //"i" --> filters
    //"j" --> Set of sets
    //"k" --> Set of nodes

    //Execute filters
    for(int i=0; i < filters.size(); ++i)
    {
        //out text buffer from previous iteration becomes new in text buffer
        in_buffer = out_buffer;
        out_buffer.clear();

        cout << "running filter: " << filters[i]->name() << endl;
        cout << "number of node sets: " << in_buffer.size() << endl;
        
        //Apply filters to all node sets.
        for(int j=0; j < in_buffer.size(); ++j)
        {
            cout << "number of strings in set: " << in_buffer[j]->size() << endl;

            //Apply filters to all nodes in the node set.
            for (int k=0; k < in_buffer[j]->size(); ++k)
            {
                //assign the results of the filter to the children vector.
                (*in_buffer[j])[k].AddChildren(filters[i]->execute((*in_buffer[j])[k].GetValue().c_str()));
                out_buffer.push_back((*in_buffer[j])[k].GetChildren());//output of first step should be 1 set of two nodes
                cout << "NUMBER OF SETS: "<< out_buffer.size() << endl;
            }//k
        }//j
    }//i

    //message the output
    output->execute();
}