// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <map>
#include <memory>
#include "../../LexerState.hpp"
#include "../../Shape.hpp"

namespace sdg {
namespace dependent_entity {

class FoundDependent : public LexerState
{
public:
    FoundDependent(Shape *context, int32_t state_code) : LexerState(context, state_code){}
    virtual ~FoundDependent() = default;

    virtual void initialize(char ch) override;
    virtual int32_t perform_scan(char ch) override;
    virtual void should_buffer(bool &should_buffer, char ch) override;
};

}// namespace dependent_entity
}// namespace sdg