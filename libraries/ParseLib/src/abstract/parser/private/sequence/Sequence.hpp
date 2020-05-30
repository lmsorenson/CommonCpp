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
    int32_t current_position_;
    Parser *context_;

    std::shared_ptr<SequenceElement> expected_element() const;
    std::shared_ptr<SequenceElement> next_expected_element() const;
    int32_t next_element_position() const;

public:
    explicit Sequence(Parser *parser);
    explicit Sequence(Parser *parser, std::vector<SequencePosition> position_vector, Cardinality cardinality = Cardinality::One);
    ~Sequence() = default;

    virtual bool evaluate(std::string token, std::function<void()> next_element, std::function<void(int32_t type, std::string message)> handle_error) override;

    void add_type(std::shared_ptr<SequenceElement> a_new_type);
    template<class ... Types> int32_t add_subsequence(Cardinality cardinality, std::shared_ptr<Types>... a_token_types);
    void evaluate_type(std::string a_token, int32_t &sequence_size, int32_t &sequence_position);
};

template<class ... Types>
int32_t Sequence::add_subsequence(Cardinality cardinality, std::shared_ptr<Types>... a_token_types )
{
    if(!context_) return 1;

    //create a vector of sequence positions from the passed in elements
    std::vector<SequencePosition> position_vector = { SequencePosition(this, a_token_types)... };

    //create a subsequence from the position vector
    std::shared_ptr<Sequence> subsequence = std::make_shared<Sequence>(context_, position_vector, cardinality);

    this->add_type(subsequence);

    return 0;
}

}// namespace parse
}// namespace sdg