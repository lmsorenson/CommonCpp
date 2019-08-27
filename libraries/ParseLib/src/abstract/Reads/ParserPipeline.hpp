// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include <string>
#include "ParserFilter.hpp"
#include "ParserOutput.hpp"
#include "node.hpp"
#include "../DataStructures/plDataSet.hpp"


typedef std::vector<std::vector<std::shared_ptr<node>>> plNodeBuffer;
typedef std::vector<std::shared_ptr<node>> plNodeSet;
typedef std::shared_ptr<node> plNodePtr;

class ParserPipeline
{
    std::vector<std::shared_ptr<ParserFilter>> filters;
    std::shared_ptr<ParserOutput> output;

    //pipeline steps
    void ProcessResults(std::vector<node> node_vec);
    int32_t ApplyFilters(plDataSet &data_set, plNodeBuffer &out_buffer, plNodeBuffer in_buffer);
    int32_t ProcessNodeSets(plNodeBuffer &out_buffer, plNodeBuffer in_buffer, std::shared_ptr<ParserFilter> filter);
    
public:
    ParserPipeline();
    ~ParserPipeline();

    int32_t add_filter(std::shared_ptr<ParserFilter> filter);
    int32_t add_output(std::shared_ptr<ParserOutput> output);
    int32_t execute(std::shared_ptr<node>& text, plDataSet& data_store);

    enum : int32_t
    {
        PIPELINE_SUCCESS=0,
        PIPELINE_FORMAT_ERROR,
        PIPELINE_UNKNOWN_ERROR
    };
};