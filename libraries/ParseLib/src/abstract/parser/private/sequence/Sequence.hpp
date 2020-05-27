// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "SequenceElement.hpp"
#include "SequencePosition.hpp"

namespace sdg {

class Parser;

namespace parse {

class Sequence : public SequenceElement
{
    std::vector<SequencePosition> position_;
    int current_position_;
    Parser *context_;

public:
    Sequence(Parser *parser) : context_(parser), current_position_(0){}
    ~Sequence() = default;
    void add_type(SequenceElement a_new_type);
    void evaluate_type(std::string token);
};

class RecurrentSequence : public Sequence
{
};

}// namespace parser
}// namespace sdg