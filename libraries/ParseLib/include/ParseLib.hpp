#pragma once
#include <stdio.h>
#include <objects/data_set.hpp>
#include <formats/csv_data_set.hpp>
#include <memory>




namespace sdg {


struct option
{
    std::string name;
    int32_t value;
};

static const std::vector<option> DEFAULT_OPTION_VECTOR;

class ParseLib
{
public:
    int32_t read_file(sdg::DataSet& data_store, const char * filepath, std::vector<option> read_options=DEFAULT_OPTION_VECTOR);
    int32_t write_file(sdg::DataSet& data_store, const char * filepath, std::vector<option> read_options=DEFAULT_OPTION_VECTOR);

    //READ CODES
    enum : int32_t
    {
        READ_SUCCESSFUL,
        READ_FORMAT_INVALID,
        READ_FILE_NOT_FOUND,
        WRITE_SUCCESSFUL,
        UNKNOWN_ERROR
    };
};

} // namespace sdg