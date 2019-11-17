// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/Writes/WriteStrategy.hpp"






class CSV_Write : public WriteStrategy
{
    virtual void configure_pipeline(ParserPipeline &pipeline);
    virtual int32_t set_read_options(std::vector<option> read_options);

    //csv read options
    bool b_use_header_line;

public:
    CSV_Write()=default;
    ~CSV_Write()=default;
};