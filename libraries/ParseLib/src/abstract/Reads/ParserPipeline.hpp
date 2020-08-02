// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include <string>
#include "ParserFilter.hpp"
#include "ParserOutput.hpp"
#include "../intermediate/node.hpp"
#include <objects/data_set.hpp>

namespace sdg {

typedef std::vector<std::vector<std::shared_ptr<sdg::SyntaxNode>>> SyntaxNodeBuffer;
typedef std::vector<std::shared_ptr<sdg::SyntaxNode>> SyntaxNodeSet;
typedef std::shared_ptr<sdg::SyntaxNode> SyntaxNodePtr;





class ParserPipeline
{
    std::vector<std::shared_ptr<ParserFilter>> filters;
    std::shared_ptr<ParserOutput> output;

    //pipeline steps
    
    int32_t ApplyFilters(
        sdg::DataSet &data_set, 
        SyntaxNodeBuffer &out_buffer, 
        SyntaxNodeBuffer &in_buffer);

    int32_t ProcessNodeSets(
        sdg::DataSet &data_set,
        SyntaxNodeBuffer &out_buffer, 
        SyntaxNodeBuffer &in_buffer, 
        std::shared_ptr<ParserFilter> filter);

    int32_t ProcessNodes(
        sdg::DataSet &data_set,
        SyntaxNodeBuffer &out_buffer, 
        SyntaxNodeSet &in_buffer, 
        std::shared_ptr<ParserFilter> filter);

    int32_t ProcessIndividual(
        sdg::DataSet &data_set,
        SyntaxNodeSet &out_buffer, 
        std::vector<sdg::SyntaxNode> &in_buffer, 
        SyntaxNodePtr &current_node, 
        std::shared_ptr<ParserFilter> filter);
    
public:
    ParserPipeline() = default;
    ~ParserPipeline() = default;

    int32_t add_filter(std::shared_ptr<ParserFilter> filter);
    int32_t add_output(std::shared_ptr<ParserOutput> output);
    int32_t execute(std::shared_ptr<sdg::SyntaxNode>& text, sdg::DataSet& data_store);
    int32_t inverse(const std::vector<std::vector<std::string>> &vector_vector, std::string &text);

    enum : int32_t
    {
        PIPELINE_SUCCESS=0,
        PIPELINE_FORMAT_ERROR,
        PIPELINE_UNKNOWN_ERROR
    };
};

}// namespace sdg