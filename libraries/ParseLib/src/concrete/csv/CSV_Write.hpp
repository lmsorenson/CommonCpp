// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/Writes/WriteStrategy.hpp"






class CSV_Write : public WriteStrategy
{
    //this method sets up the pipeline.
    virtual void configure_pipeline(sdg::ParserPipeline &pipeline) override;

    //this function reads special parameters into the write strategy.
    virtual int32_t set_write_options(std::vector<sdg::option> write_options) override;

    //this function gets all elements produced by the final filter in the pipeline.
    virtual std::vector<std::vector<std::string>> get_dataset_contents(sdg::DataSet dataset) override;

    //csv read options
    bool b_use_header_line;

public:
    CSV_Write()=default;
    ~CSV_Write()=default;
};