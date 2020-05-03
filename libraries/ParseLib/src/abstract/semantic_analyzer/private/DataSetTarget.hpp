// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <memory>
#include <objects/data_set.hpp>
#include "../../intermediate/node.hpp"

namespace sdg {

class DataSetTarget
{
    sdg::DataSet * data_set_;

public:
    DataSetTarget(sdg::DataSet *data_set_)
    : data_set_(data_set_) {}

    void add(std::string key, std::string value, std::string path);

};

}// namespace sdg