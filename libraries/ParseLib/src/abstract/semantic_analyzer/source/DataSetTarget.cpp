// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../private/DataSetTarget.hpp"
#include <iostream>
#include <vector>

using ::std::string;
using ::std::vector;
using ::sdg::DataSet;
using ::sdg::DataSetTarget;
using ::std::cout;
using ::std::endl;
using ::sdg::hash::KeyInstance;



void DataSetTarget::add(string key, string value, string path)
{
        data_set_->set( KeyInstance(key), sdg::plHashValue( value, path ) );
}