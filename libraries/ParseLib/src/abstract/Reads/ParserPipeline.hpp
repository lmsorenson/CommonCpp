// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include <string>
#include "ParserFilter.hpp"
#include "ParserOutput.hpp"
#include "../DataStructures/plNode.hpp"
#include "../DataStructures/plDataSet.hpp"


typedef std::vector<std::vector<std::shared_ptr<plNode>>> plNodeBuffer;
typedef std::vector<std::shared_ptr<plNode>> plNodeSet;
typedef std::shared_ptr<plNode> plNodePtr;

class ParserPipeline
{
    std::vector<std::shared_ptr<ParserFilter>> filters;
    std::shared_ptr<ParserOutput> output;

    //pipeline steps
    
    int32_t ApplyFilters(
        plDataSet &data_set, 
        plNodeBuffer &out_buffer, 
        plNodeBuffer &in_buffer);

    int32_t ProcessNodeSets(
        plNodeBuffer &out_buffer, 
        plNodeBuffer &in_buffer, 
        std::shared_ptr<ParserFilter> filter);

    int32_t ProcessNodes(
        plNodeBuffer &out_buffer, 
        plNodeSet &in_buffer, 
        std::shared_ptr<ParserFilter> filter);

    int32_t ProcessIndividual(
        plNodeSet &out_buffer, 
        std::vector<plNode> &in_buffer, 
        plNodePtr &current_node, 
        std::shared_ptr<ParserFilter> filter);
    
public:
    ParserPipeline() = default;
    ~ParserPipeline() = default;

    int32_t add_filter(std::shared_ptr<ParserFilter> filter);
    int32_t add_output(std::shared_ptr<ParserOutput> output);
    int32_t execute(std::shared_ptr<plNode>& text, plDataSet& data_store);

    enum : int32_t
    {
        PIPELINE_SUCCESS=0,
        PIPELINE_FORMAT_ERROR,
        PIPELINE_UNKNOWN_ERROR
    };

    
};