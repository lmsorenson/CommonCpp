// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../../abstract/Reads/ReadStrategy.hpp"



class ReadCSV : public ReadStrategy
{
    virtual void configure_pipeline(ParserPipeline &pipeline);
    virtual int32_t set_read_options(std::vector<sdg::option> read_options);

    //csv read options
    bool b_use_header_line;

public:
    ReadCSV();
    ~ReadCSV();
};