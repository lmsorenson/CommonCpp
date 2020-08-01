// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>
#include <iostream>
#include "SequenceElement.hpp"
#include "SequencePosition.hpp"
#include "../../public/DependentEntity.hpp"

namespace sdg {

class Parser;

namespace parse {

class TokenType;

class Sequence : public SequenceElement
{
public:
    explicit Sequence(Parser *parser, std::string name = "Unknown sequence", Cardinality cardinality = Cardinality::One);
    virtual ~Sequence() = default;

    virtual void print() const override;

    //evaluate the current sequence position.  
    std::shared_ptr<TokenType> match_token(std::string a_token);
    virtual std::shared_ptr<TokenType> evaluate(const std::string &token, MatchStatus &status) override;

    std::shared_ptr<SequenceElement> next_expected_element() const;
    void go_to_next_item();

    //setup and construction methods
    void add_element(std::shared_ptr<SequenceElement> a_new_type);
    void set_positions(std::vector<std::shared_ptr<SequencePosition>> position_vector);
    template<class ... Types> int32_t add_subsequence(std::string name, Cardinality cardinality, std::shared_ptr<Types>... a_token_types);

private:
    Parser *context_;
    std::string name_;
    std::vector<std::shared_ptr<SequencePosition>> position_;
    int32_t current_position_;

    std::shared_ptr<SequenceElement> expected_element() const;
    int32_t next_element_position() const;
    void handle_error(int32_t error_code, std::string message) const;
    void set_position();
};




template<class ... Types>
int32_t Sequence::add_subsequence(std::string name, Cardinality cardinality, std::shared_ptr<Types>... a_token_type_pack )
{
    if(!context_) return 1;

    std::shared_ptr<Sequence> subsequence = std::make_shared<Sequence>(context_, name, cardinality);
     
    //create a vector of sequence positions from the passed in elements
    std::vector<std::shared_ptr<SequencePosition>> position_vector = { std::make_shared<SequencePosition>(subsequence.get(), a_token_type_pack)... };

    for (long unsigned int i=0; i<position_vector.size(); i++)
    {
        std::shared_ptr dependent = std::dynamic_pointer_cast<DependentEntity>(position_vector[i]->item());
        if (dependent && (i-1)>=0)
        {
            std::shared_ptr object = std::dynamic_pointer_cast<TokenType>(position_vector[i-1]->item());
            if(object)
            {
                dependent->dependent_on(object);
            }
        }
    }

    subsequence->set_positions(position_vector); 

    this->add_element(subsequence);

    return 0;
}

}// namespace parse
}// namespace sdg