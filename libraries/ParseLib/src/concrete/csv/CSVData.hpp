// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../../abstract/DataStructures/InstanceSet.hpp"
#include <vector>
#include <string>

typedef std::string field;
typedef std::vector<field> record;
typedef std::vector<record> csv_file;

class CSVData : public InstanceSet
{
    csv_file file;

public:
    CSVData() = default;
    CSVData(int32_t hash_table_size);
    ~CSVData();

    virtual void assign();
};