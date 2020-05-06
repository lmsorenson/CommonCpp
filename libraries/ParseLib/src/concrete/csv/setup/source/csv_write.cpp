// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../csv_write.hpp"
#include "../../csv_filters.hpp"


using ::std::shared_ptr;



void sdg::csv::Write::configure_pipeline(::sdg::ParserPipeline & pipeline)
{
    if(this->b_use_header_line)
        pipeline.add_filter(std::shared_ptr<HeaderFilter> (new HeaderFilter("~H")));

    pipeline.add_filter(shared_ptr<RecordFilter> (new RecordFilter("R")));
    pipeline.add_filter(shared_ptr<FieldFilter> (new FieldFilter("F")));
    pipeline.add_output(shared_ptr<CSVOutput> (new CSVOutput()));
}

int32_t sdg::csv::Write::set_write_options(std::vector<sdg::option> write_options)
{
    for (auto option : write_options)
    {
        if((option.name == "header_line") && (option.value>0))
            this->b_use_header_line = true;
    }

    return 0;
}

std::vector<std::vector<std::string>> sdg::csv::Write::get_dataset_contents(sdg::DataSet dataset)
{
    std::vector<std::vector<std::string>> return_var;

    for(int32_t i=0; i<dataset.number_of_entity_instances(hash::EntityID("R")); ++i)
    {
        hash::DescriptorInstance descriptor("R", Attribute::Scale::Numeric);
        descriptor.set_value(i);

        return_var.push_back(dataset.get(hash::KeyInstance({descriptor})).get_vector());
    }

    return return_var;
}