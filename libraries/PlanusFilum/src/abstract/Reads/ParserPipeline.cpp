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

void ParserPipeline::execute(std::shared_ptr<node>& text, AbstractDataStructure& data_store)
{
    cout << "executing pipeline. . . " << endl;
    cout << "number of filters: " << filters.size() << endl;

    vector<vector<shared_ptr<node>>> in_buffer;
    vector<vector<shared_ptr<node>>> out_buffer;
    
    cout << "copy input text. . . " << endl;
    vector<shared_ptr<node>> svn;
    svn.push_back(text);
    out_buffer.push_back(svn);
    cout << "finish copy input text. . . " << endl;
    

    //for loops
    //"i" --> filters
    //"j" --> Set of sets
    //"k" --> Set of nodes

    //Execute filters
    for(int i=0; i < filters.size(); ++i)
    {
        // out text buffer from previous filter becomes new in text buffer
        in_buffer = out_buffer;
        out_buffer.clear();

        cout << endl << "FILTER: " << filters[i]->name() << endl;
        cout << "FILTER: number of node sets: " << in_buffer.size() << endl;
        
        // Apply filters to all node sets.
        for(int j=0; j < in_buffer.size(); ++j)
        {
            cout << "NODE SET: number of strings in set: " << in_buffer[j].size() << endl;

            // Apply filters to all nodes in the node set.
            for (int k=0; k < in_buffer[j].size(); ++k)
            {
                //assign the results of the filter to the children vector.
                string str = in_buffer[j][k]->GetValue();
                cout << "NODE: extract string - " << str << endl;
                

                vector<shared_ptr<node>> filter_result_set;
                vector<node> vn = filters[i]->execute(str.c_str());

                //Breakup the filter output.
                for(int l = 0; l < vn.size(); ++l)
                {
                    cout << "FILTER: " << vn[l].GetValue() << endl;
                    
                    //Add this to the child
                    in_buffer[j][k]->AddChild(node(vn[l].GetValue().c_str()));

                    //Will be added to the output buffer
                    filter_result_set.push_back(in_buffer[j][k]->GetChild(l));
                }

                cout << "NODE: filter result size - " << filter_result_set.size() << endl;

                out_buffer.push_back(filter_result_set);//output of first step should be 1 set of two nodes
                cout << "NODE: NUMBER OF SETS: "<< out_buffer.size() << endl;

                filter_result_set.clear();
            }//k
        }//j        
    }//i

    cout << "clearing vectors" << endl;
    in_buffer.clear();
    out_buffer.clear();
    cout << "done clearing vectors" << endl;
    
    //message the output
    output->execute(text, data_store);
}