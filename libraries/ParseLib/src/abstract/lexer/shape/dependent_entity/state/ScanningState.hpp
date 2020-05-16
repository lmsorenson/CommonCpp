// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <map>
#include <memory>
#include "../../LexerState.hpp"
#include "../../Shape.hpp"

namespace sdg {
namespace dependent_entity {

class Scanning : public LexerState
{
public:
    Scanning(Shape *context) : LexerState(context){}

    virtual void initialize(char ch) override;
    virtual void perform_scan(char ch) override;
    virtual void should_buffer(bool &should_buffer, char ch) override;
};

}// namespace dependent_entity
}// namespace sdg