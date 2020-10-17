#pragma once
#include <stdio.h>
#include <objects/data_set.hpp>
#include <formats/csv_data_set.hpp>
#include "../src/abstract/Factories/AbstractFactory.hpp"
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
    virtual int32_t read_file(sdg::DataSet& data_store, const char * filepath, std::vector<option> read_options=DEFAULT_OPTION_VECTOR);
    virtual int32_t write_file(sdg::DataSet& data_store, const char * filepath, std::vector<option> read_options=DEFAULT_OPTION_VECTOR);

    //READ CODES
    enum : int8_t
    {
        READ_SUCCESSFUL = 0,
        READ_FORMAT_INVALID,
        READ_FILE_NOT_FOUND,
        WRITE_SUCCESSFUL,
        UNKNOWN_ERROR
    };

private:
    virtual std::shared_ptr<class AbstractFactory> produce_factory() const;

    std::shared_ptr<class AbstractFactory> factory_;
};

} // namespace sdg