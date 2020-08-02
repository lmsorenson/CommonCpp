// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "ParserPipeline.hpp"
#include <iostream>
#include <vector>


#include "../../utils/stopwatch.hpp"


using std::shared_ptr;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::fixed;
using std::flush;
using sdg::SyntaxNode;
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
int32_t ParserPipeline::execute(std::shared_ptr<SyntaxNode>& text, sdg::DataSet& data_store)
{
    utils::Stopwatch sw;
    sw.start();

    int32_t result;

    vector<vector<shared_ptr<SyntaxNode>>> in_buffer;
    vector<vector<shared_ptr<SyntaxNode>>> out_buffer;
    
    vector<shared_ptr<SyntaxNode>> svn;
    svn.push_back(text);
    out_buffer.push_back(svn);


    if ((result = this->ApplyFilters(data_store, out_buffer, in_buffer)) != PIPELINE_SUCCESS)
    {
        return result;
    }

    in_buffer.clear();
    out_buffer.clear();
    
    sw.stop();
    cout << fixed << "ParserPipeline takes: " <<  sw.read_seconds() << "s" << endl;

    //message the output
    output->execute(text, data_store);

    return PIPELINE_SUCCESS;
}

int32_t ParserPipeline::inverse(const std::vector<std::vector<std::string>> &vector_vector, std::string &text)
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

int32_t ParserPipeline::ProcessIndividual(sdg::DataSet &data_set, SyntaxNodeSet &out_buffer, vector<SyntaxNode> &in_buffer, SyntaxNodePtr &current_node, std::shared_ptr<ParserFilter> filter)
{
    //Breakup the filter output.
    for(int l = 0; l < in_buffer.size(); ++l)
    {
        //create a new SyntaxNode to be added to the tree
        SyntaxNode newNode = SyntaxNode(in_buffer[l].get_item_value().c_str(), current_node);

            //Append the id of the parent SyntaxNode
            newNode.append_key(current_node->get_item_key());
            
            //add the delimiter
            if(!newNode.is_empty_key())
                newNode.append_key("-");

            //functionality for the special (~) flag
            if (filter->GetLabel().substr(0,1)=="~")
            {
                if (l==0)
                {
                    newNode.append_key(filter->GetLabel().substr(1));
                }
            }
            //Append the id of this SyntaxNode
            else 
            {
                newNode.append_key(filter->GetID(l));
            }
                

        //Add this to the current SyntaxNode's child set.
        current_node->AddChild(newNode);

        //Will be added to the output buffer.
        out_buffer.push_back(current_node->get_child(l));
    }//vector

    return PIPELINE_SUCCESS;

}

int32_t ParserPipeline::ProcessNodes(sdg::DataSet &data_set, SyntaxNodeBuffer &out_buffer, SyntaxNodeSet &in_buffer, std::shared_ptr<ParserFilter> filter)
{
    // Apply filters to all nodes in the SyntaxNode set.
    for (int k=0; k < in_buffer.size(); ++k)
    {
        //assign the results of the filter to the children vector.
        string str = in_buffer[k]->get_item_value();

        vector<shared_ptr<SyntaxNode>> filter_result_set;
        
        vector<SyntaxNode> vn;
        int32_t err;
        if( (err=filter->execute(str.c_str(), vn))!=ParserFilter::FILTER_SUCCESS )
        {
            switch (err)
            {
                case ParserFilter::FILTER_FORMAT_ERROR: return PIPELINE_FORMAT_ERROR; break;
                default: return PIPELINE_UNKNOWN_ERROR; break;
            }
        }

        int32_t result;
        if ((result=this->ProcessIndividual(data_set, filter_result_set, vn, in_buffer[k], filter))!=PIPELINE_SUCCESS)
        {
            return result;
        }

        out_buffer.push_back(filter_result_set);
        filter_result_set.clear();
    }//k

    return PIPELINE_SUCCESS;
}

int32_t ParserPipeline::ProcessNodeSets(sdg::DataSet &data_set, SyntaxNodeBuffer &out_buffer, SyntaxNodeBuffer &in_buffer, shared_ptr<ParserFilter> filter)
{
    int32_t result;

    // Apply filters to all SyntaxNode sets.
    for(int j=0; j < in_buffer.size(); ++j)
    {
        if ((result=ProcessNodes(data_set, out_buffer, in_buffer[j], filter))!= PIPELINE_SUCCESS)
        {
            return result;
        }
    }//j        

    return PIPELINE_SUCCESS;
}

int32_t ParserPipeline::ApplyFilters(sdg::DataSet &data_set, SyntaxNodeBuffer &out_buffer, SyntaxNodeBuffer &in_buffer)
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