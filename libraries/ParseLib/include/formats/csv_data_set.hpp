// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once

#include <objects/data_set.hpp>
#include <vector>
#include <string>

namespace sdg {

typedef std::string field;
typedef std::vector<field> record;
typedef std::vector<record> csv_file;

class CSV : public sdg::DataSet
{
    csv_file file;

    void csv_model();

public:
    CSV();
    CSV(int32_t hash_table_size);
    ~CSV();

    virtual void assign();
    virtual void add_instance(std::string entity_id, std::vector<std::string> entity_values, int32_t position=-1) override;
    virtual void remove_instance(std::string entity_id) override;;
    virtual void increment_instance_id(std::string entity_id, int32_t position=1) override;
    virtual int32_t pad_entity_count(std::string entity_id, int32_t a_num_blanks=1) override;
};

}// namespace sdg