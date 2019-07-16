// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../../abstract/Reads/ReadStrategy.hpp"



class ReadCSV : public ReadStrategy
{
    virtual void configure_pipeline(ParserPipeline &pipeline);
    virtual std::vector<std::vector<std::string>> parse(const char * file_contents);
    virtual std::string select();

public:
    ReadCSV();
    ~ReadCSV();
};