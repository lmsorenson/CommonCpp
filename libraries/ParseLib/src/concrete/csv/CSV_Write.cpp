// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSV_Write.hpp"
#include "CSVFilters.hpp"




using namespace std;

void CSV_Write::configure_pipeline(ParserPipeline & pipeline)
{
    if(this->b_use_header_line)
        pipeline.add_filter(std::shared_ptr<HeaderFilter> (new HeaderFilter("~H")));

    pipeline.add_filter(shared_ptr<RecordFilter> (new RecordFilter("R")));
    pipeline.add_filter(shared_ptr<FieldFilter> (new FieldFilter("F")));
    pipeline.add_output(shared_ptr<CSVOutput> (new CSVOutput()));
}

int32_t CSV_Write::set_write_options(std::vector<option> write_options)
{
    for (auto option : write_options)
    {
        if((option.name == "header_line") && (option.value>0))
            this->b_use_header_line = true;
    }

    return 0;
}

std::vector<std::vector<std::string>> CSV_Write::get_dataset_contents(sdg::plDataSet dataset)
{
    std::vector<std::vector<std::string>> return_var;

    for(int32_t i=0; i<dataset.number_of_entity_instances("R"); ++i)
    {
        std::string index = "R";
        index.append(std::to_string(i));

        return_var.push_back(dataset.get(index).get_vector());
    }

    return return_var;
}