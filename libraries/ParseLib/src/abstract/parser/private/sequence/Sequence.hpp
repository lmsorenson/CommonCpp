// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>
#include <iostream>
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
    explicit Sequence(Parser *parser) : context_(parser), current_position_(0){}
    explicit Sequence(Parser *parser, std::vector<SequencePosition> position_vector): context_(parser), position_(position_vector){}
    ~Sequence() = default;

    void add_type(std::shared_ptr<SequenceElement> a_new_type);
    template<class ... Types> int32_t add_subsequence(std::shared_ptr<Types>... a_token_types);
    void evaluate_type(std::string a_token, int32_t &sequence_size, int32_t &sequence_position);
};

template<class ... Types>
int32_t Sequence::add_subsequence(std::shared_ptr<Types>... a_token_types)
{
    if(!context_) return 1;

    //create a vector of sequence positions from the passed in elements
    std::vector<SequencePosition> position_vector = { SequencePosition(this, a_token_types)... };

    //create a subsequence from the position vector
    std::shared_ptr<Sequence> subsequence = std::make_shared<Sequence>(context_, position_vector);

    this->add_type(subsequence);

    return 0;
}

}// namespace parser
}// namespace sdg