// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include <string>
#include "ParserFilter.hpp"
#include "ParserOutput.hpp"
#include "../data/structures/node.hpp"
#include <objects/data_set.hpp>


typedef std::vector<std::vector<std::shared_ptr<sdg::plNode>>> plNodeBuffer;
typedef std::vector<std::shared_ptr<sdg::plNode>> plNodeSet;
typedef std::shared_ptr<sdg::plNode> plNodePtr;

class ParserPipeline
{
    std::vector<std::shared_ptr<ParserFilter>> filters;
    std::shared_ptr<ParserOutput> output;

    //pipeline steps
    
    int32_t ApplyFilters(
        sdg::DataSet &data_set, 
        plNodeBuffer &out_buffer, 
        plNodeBuffer &in_buffer);

    int32_t ProcessNodeSets(
        sdg::DataSet &data_set,
        plNodeBuffer &out_buffer, 
        plNodeBuffer &in_buffer, 
        std::shared_ptr<ParserFilter> filter);

    int32_t ProcessNodes(
        sdg::DataSet &data_set,
        plNodeBuffer &out_buffer, 
        plNodeSet &in_buffer, 
        std::shared_ptr<ParserFilter> filter);

    int32_t ProcessIndividual(
        sdg::DataSet &data_set,
        plNodeSet &out_buffer, 
        std::vector<plNode> &in_buffer, 
        plNodePtr &current_node, 
        std::shared_ptr<ParserFilter> filter);
    
public:
    ParserPipeline() = default;
    ~ParserPipeline() = default;

    int32_t add_filter(std::shared_ptr<ParserFilter> filter);
    int32_t add_output(std::shared_ptr<ParserOutput> output);
    int32_t execute(std::shared_ptr<plNode>& text, sdg::DataSet& data_store);
    int32_t inverse(std::vector<std::vector<std::string>> vector_vector, std::string &text);

    enum : int32_t
    {
        PIPELINE_SUCCESS=0,
        PIPELINE_FORMAT_ERROR,
        PIPELINE_UNKNOWN_ERROR
    };

    
};
