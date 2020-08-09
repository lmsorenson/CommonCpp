#pragma once
#include <objects/data_set.hpp>

class TestDataSet : public ::sdg::DataSet
{
public:
    TestDataSet(::sdg::DataSet::State state = ::sdg::DataSet::State::DATA_SET_EMPTY);
    virtual ~TestDataSet() = default;
};
