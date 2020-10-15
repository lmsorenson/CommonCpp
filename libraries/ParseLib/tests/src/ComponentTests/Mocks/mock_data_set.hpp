#pragma once
#include <objects/data_set.hpp>

class MockDataSet : public ::sdg::DataSet
{
public:
    MockDataSet(::sdg::DataSet::State state = ::sdg::DataSet::State::DATA_SET_EMPTY);
    virtual ~MockDataSet() = default;

    void use_mock_facade(::std::shared_ptr<class ::sdg::ParseLib> facade);
};
