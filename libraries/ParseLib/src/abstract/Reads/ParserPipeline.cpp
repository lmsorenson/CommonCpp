// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ParserPipeline.hpp"
#include <iostream>
#include <vector>


using namespace std;


void RunFilters();
void NodeSets();
void Nodes();



ParserPipeline::ParserPipeline(){}
ParserPipeline::~ParserPipeline(){}

int32_t ParserPipeline::add_filter(shared_ptr<ParserFilter> filter)
{
    filters.push_back(filter);
    return 0;
}

int32_t ParserPipeline::add_output(shared_ptr<ParserOutput> output)
{
    this->output = output;
    return 0;
}

//execute will populate the plDataSet
int32_t ParserPipeline::execute(std::shared_ptr<node>& text, plDataSet& data_store)
{
    int32_t result;

    vector<vector<shared_ptr<node>>> in_buffer;
    vector<vector<shared_ptr<node>>> out_buffer;
    
    vector<shared_ptr<node>> svn;
    svn.push_back(text);
    out_buffer.push_back(svn);


    if ((result = this->ApplyFilters(data_store, out_buffer, in_buffer)) != PIPELINE_SUCCESS)
    {
        return result;
    }

    in_buffer.clear();
    out_buffer.clear();
    
    //message the output
    output->execute(text, data_store);

    return PIPELINE_SUCCESS;
}

void ParserPipeline::ProcessResults(vector<node> node_vec)
{
    for(int l = 0; l < node_vec.size(); ++l)
    {

    }
}

int32_t ParserPipeline::ProcessNodeSets(plNodeBuffer &out_buffer, plNodeBuffer in_buffer, shared_ptr<ParserFilter> filter)
{

    // Apply filters to all node sets.
        for(int j=0; j < in_buffer.size(); ++j)
        {
            // Apply filters to all nodes in the node set.
            for (int k=0; k < in_buffer[j].size(); ++k)
            {
                //assign the results of the filter to the children vector.
                string str = in_buffer[j][k]->GetValue();

                vector<shared_ptr<node>> filter_result_set;
                
                vector<node> vn;
                int32_t err;
                if( (err=filter->execute(str.c_str(), vn))!=ParserFilter::FILTER_SUCCESS )
                {
                    switch (err)
                    {
                        case ParserFilter::FILTER_FORMAT_ERROR: return PIPELINE_FORMAT_ERROR; break;
                        default: return PIPELINE_UNKNOWN_ERROR; break;
                    }
                }

                //Breakup the filter output.
                for(int l = 0; l < vn.size(); ++l)
                {
                    //create a new node to be added to the tree
                    node newNode = node(vn[l].GetValue().c_str(), in_buffer[j][k]);

                        //Append the id of the parent node
                        newNode.AppendID(in_buffer[j][k]->GetID());
                        
                        //add the delimiter
                        if(!newNode.EmptyID())
                            newNode.AppendID("-");

                        //Append the id of this node
                        newNode.AppendID(filter->GetID(l));

                    //Add this to the current node's child set.
                    in_buffer[j][k]->AddChild(newNode);

                    //Will be added to the output buffer.
                    filter_result_set.push_back(in_buffer[j][k]->GetChild(l));
                }

                out_buffer.push_back(filter_result_set);
                filter_result_set.clear();
            }//k
        }//j        

    return PIPELINE_SUCCESS;
}

int32_t ParserPipeline::ApplyFilters(plDataSet &data_set, plNodeBuffer &out_buffer, plNodeBuffer in_buffer)
{
    int32_t result;
     //for loops
    //"i" --> filters
    //"j" --> Set of sets
    //"k" --> Set of nodes

    for(int i=0; i < filters.size(); ++i)
    {
        // out text buffer from previous filter becomes new in text buffer
        in_buffer = out_buffer;
        out_buffer.clear();

        //add information about the filtered data to the resulting data set.
        data_set.add_label(filters[i]->GetLabel());

        if ((result=this->ProcessNodeSets(out_buffer, in_buffer, filters[i]))!=PIPELINE_SUCCESS)
        {
            return result;
        }        
    }//i
    return PIPELINE_SUCCESS;
}