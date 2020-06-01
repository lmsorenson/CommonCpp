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

class TokenType;

class Sequence : public SequenceElement
{
    std::string name_;
    Parser *context_;
    std::vector<std::shared_ptr<SequencePosition>> position_;
    int32_t current_position_;

    std::shared_ptr<SequenceElement> expected_element() const;
    int32_t next_element_position() const;
    void handle_error(int32_t error_code, std::string message) const;
    void set_position();

public:
    explicit Sequence(Parser *parser, std::string name = "Unknown sequence", Cardinality cardinality = Cardinality::One);
    ~Sequence() = default;

    std::shared_ptr<SequenceElement> next_expected_element() const;

    virtual std::shared_ptr<TokenType> evaluate(std::string token, std::function<void()> next_element, std::function<void(int32_t type, std::string message)> handle_error, MatchStatus &status) override;
    std::shared_ptr<TokenType> match_token(std::string a_token, int32_t &sequence_size, int32_t &sequence_position);
    virtual void print() const override;

    void add_element(std::shared_ptr<SequenceElement> a_new_type);
    void set_positions(std::vector<std::shared_ptr<SequencePosition>> position_vector);
    template<class ... Types> int32_t add_subsequence(std::string name, Cardinality cardinality, std::shared_ptr<Types>... a_token_types);
};

template<class ... Types>
int32_t Sequence::add_subsequence(std::string name, Cardinality cardinality, std::shared_ptr<Types>... a_token_type_pack )
{
    if(!context_) return 1;

    std::shared_ptr<Sequence> subsequence = std::make_shared<Sequence>(context_, name, cardinality);
     
    //create a vector of sequence positions from the passed in elements
    std::vector<std::shared_ptr<SequencePosition>> position_vector = { std::make_shared<SequencePosition>(subsequence.get(), a_token_type_pack)... };

    subsequence->set_positions(position_vector); 

    this->add_element(subsequence);

    return 0;
}

}// namespace parse
}// namespace sdg