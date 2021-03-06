// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <map>
#include <memory>
#include "../../LexerState.hpp"
#include "../../Shape.hpp"

namespace sdg {
namespace dependent_entity {

class ScanningEscaped : public LexerState
{
    enum : int32_t
    {
        Open,
        Closed
    };
    int32_t num_delimiters;

public:
    ScanningEscaped(Shape *context, int32_t state_code) : LexerState(context, state_code), num_delimiters(0) {}
    virtual ~ScanningEscaped() = default;

    virtual void initialize(char ch) override;
    virtual void on_transition() override;
    virtual int32_t perform_scan(char ch) override;
    virtual void should_buffer(bool &should_buffer, char ch) override;
    virtual void update() override;
};

}// namespace dependent_entity
}// namespace sdg