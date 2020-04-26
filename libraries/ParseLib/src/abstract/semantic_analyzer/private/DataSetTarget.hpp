// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <memory>
#include <objects/data_set.hpp>

namespace sdg {

class DataSetTarget
{
    std::shared_ptr<sdg::DataSet> data_set_;

public:
    DataSetTarget(std::shared_ptr<sdg::DataSet> data_set_)
    : data_set_(data_set_) {}

    void add_to_root(std::string id, std::string value);
    void add_to_node(std::vector<int> path, std::string id, std::string value);
};

}// namespace sdg