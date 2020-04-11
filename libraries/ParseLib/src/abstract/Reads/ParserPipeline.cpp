// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ParserPipeline.hpp"
#include <iostream>
#include <vector>


using std::shared_ptr;
using std::vector;
using std::string;
using sdg::plNode;
using sdg::ParserPipeline;



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

//execute will populate the DataSet
int32_t ParserPipeline::execute(std::shared_ptr<plNode>& text, sdg::DataSet& data_store)
{
    int32_t result;

    vector<vector<shared_ptr<plNode>>> in_buffer;
    vector<vector<shared_ptr<plNode>>> out_buffer;
    
    vector<shared_ptr<plNode>> svn;
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

int32_t ParserPipeline::inverse(std::vector<std::vector<std::string>> vector_vector, std::string &text)
{
    std::string compiled_buffer;
    std::vector<std::vector<std::string>> vector_in_buffer;
    std::vector<std::vector<std::string>> vector_out_buffer = vector_vector;

    for(int i=0; i < filters.size(); ++i)
    {
        vector_in_buffer.clear();
        vector_in_buffer = vector_out_buffer;
        vector_out_buffer.clear();

        std::vector<std::string> vec_out;

        int32_t result;
        for(int k=0; k < vector_in_buffer.size(); ++k)
        {
            //1 given 1 record separated into a vector.
            //2 given 1 dataset separated into a vector of records.
            //empty compiled_string
            compiled_buffer.clear();

            int32_t err;
            if( (err=filters[i]->inverse(vector_in_buffer[k], compiled_buffer))!=ParserFilter::FILTER_SUCCESS )
            {
                switch (err)
                {
                    case ParserFilter::FILTER_FORMAT_ERROR: return PIPELINE_FORMAT_ERROR; break;
                    default: return PIPELINE_UNKNOWN_ERROR; break;
                }
            }

            //1 give me 1 string each value separated by a comma
            //2 give me 1 string each record separated by a line break.
            vec_out.push_back(compiled_buffer);
        }//k

        //after going through all of the vectors push back
        vector_out_buffer.push_back(vec_out);

    }//i
        

    
    text = compiled_buffer;
    return PIPELINE_SUCCESS;
}

int32_t ParserPipeline::ProcessIndividual(sdg::DataSet &data_set, plNodeSet &out_buffer, vector<plNode> &in_buffer, plNodePtr &current_node, std::shared_ptr<ParserFilter> filter)
{
    //Breakup the filter output.
    for(int l = 0; l < in_buffer.size(); ++l)
    {
        //create a new plNode to be added to the tree
        plNode newNode = plNode(in_buffer[l].GetValue().c_str(), current_node);

            //Append the id of the parent plNode
            newNode.AppendID(current_node->GetID());
            
            //add the delimiter
            if(!newNode.EmptyID())
                newNode.AppendID("-");

            //functionality for the special (~) flag
            if (filter->GetLabel().substr(0,1)=="~")
            {
                if (l==0)
                {
                    newNode.AppendID(filter->GetLabel().substr(1));
                }
            }
            //Append the id of this plNode
            else 
            {
                newNode.AppendID(filter->GetID(l));
            }
                

        //Add this to the current plNode's child set.
        current_node->AddChild(newNode);

        //Will be added to the output buffer.
        out_buffer.push_back(current_node->GetChild(l));
    }//vector

    return PIPELINE_SUCCESS;

}

int32_t ParserPipeline::ProcessNodes(sdg::DataSet &data_set, plNodeBuffer &out_buffer, plNodeSet &in_buffer, std::shared_ptr<ParserFilter> filter)
{
    int32_t result;

    // Apply filters to all nodes in the plNode set.
    for (int k=0; k < in_buffer.size(); ++k)
    {
        //assign the results of the filter to the children vector.
        string str = in_buffer[k]->GetValue();

        vector<shared_ptr<plNode>> filter_result_set;
        
        vector<plNode> vn;
        int32_t err;
        if( (err=filter->execute(str.c_str(), vn))!=ParserFilter::FILTER_SUCCESS )
        {
            switch (err)
            {
                case ParserFilter::FILTER_FORMAT_ERROR: return PIPELINE_FORMAT_ERROR; break;
                default: return PIPELINE_UNKNOWN_ERROR; break;
            }
        }

        if ((result=this->ProcessIndividual(data_set, filter_result_set, vn, in_buffer[k], filter))!=PIPELINE_SUCCESS)
        {
            return result;
        }

        out_buffer.push_back(filter_result_set);
        filter_result_set.clear();
    }//k

    return PIPELINE_SUCCESS;
}

int32_t ParserPipeline::ProcessNodeSets(sdg::DataSet &data_set, plNodeBuffer &out_buffer, plNodeBuffer &in_buffer, shared_ptr<ParserFilter> filter)
{
    int32_t result;

    // Apply filters to all plNode sets.
    for(int j=0; j < in_buffer.size(); ++j)
    {
        if ((result=ProcessNodes(data_set, out_buffer, in_buffer[j], filter))!= PIPELINE_SUCCESS)
        {
            return result;
        }
    }//j        

    return PIPELINE_SUCCESS;
}

int32_t ParserPipeline::ApplyFilters(sdg::DataSet &data_set, plNodeBuffer &out_buffer, plNodeBuffer &in_buffer)
{
    int32_t result;

    for(int i=0; i < filters.size(); ++i)
    {
        // out text buffer from previous filter becomes new in text buffer
        in_buffer = out_buffer;
        out_buffer.clear();

        if ((result=this->ProcessNodeSets(data_set, out_buffer, in_buffer, filters[i]))!=PIPELINE_SUCCESS)
        {
            return result;
        }     

    }//i

    return PIPELINE_SUCCESS;
}