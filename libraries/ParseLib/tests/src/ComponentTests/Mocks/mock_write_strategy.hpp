#pragma once
#include <gmock/gmock.h>
#include <objects/data_set.hpp>
#include <WriteStrategy.hpp>

class MockWriteStrategy : public ::sdg::WriteStrategy
{
public:
    MockWriteStrategy() = default;
    virtual ~MockWriteStrategy() = default;

    MOCK_METHOD(void, configure_pipeline, (sdg::ParserPipeline &pipeline), ());
    MOCK_METHOD(int32_t, set_write_options, (std::vector<sdg::option> write_options), ());
    MOCK_METHOD(std::vector<std::vector<std::string>>, get_dataset_contents, (sdg::DataSet dataset), ());

    MOCK_METHOD(int32_t, execute_write, (sdg::DataSet dataset, std::string path), ());
};
