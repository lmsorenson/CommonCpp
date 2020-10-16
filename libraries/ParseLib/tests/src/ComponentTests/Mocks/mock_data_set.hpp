#pragma once
#include <gmock/gmock.h>
#include <objects/data_set.hpp>
#include <stdint.h>

class MockDataSet : public ::sdg::DataSet
{
public:
    MockDataSet(::sdg::DataSet::State state = ::sdg::DataSet::State::DATA_SET_EMPTY);
    virtual ~MockDataSet() = default;

    void use_mock_facade(::std::shared_ptr<class ::sdg::ParseLib> facade);

    MOCK_METHOD(void, add_instance, (sdg::hash::EntityID entity_id, std::vector<std::string> entity_values, int32_t position), (override));
    MOCK_METHOD(void, remove_instance, (::sdg::hash::KeyInstance a_key_subset), (override));
    MOCK_METHOD(void, reposition_instance, (::sdg::hash::DescriptorInstance a_descriptor, int32_t position), (const override));
};
