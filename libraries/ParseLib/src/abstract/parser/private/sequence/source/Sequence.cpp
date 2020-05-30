// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../Sequence.hpp"
#include <iostream>

#include "../SequencePosition.hpp"
#include "../../../Parser.hpp"

using std::cout;
using std::endl;
using std::shared_ptr;
using std::vector;
using std::function;
using std::dynamic_pointer_cast;
using sdg::parse::Sequence;
using sdg::parse::SequenceElement;


Sequence::Sequence(Parser *parser) 
: SequenceElement(Cardinality::One)
, context_(parser)
, current_position_(0)
{}

Sequence::Sequence(Parser *parser, vector<SequencePosition> position_vector, Cardinality cardinality)
: SequenceElement(cardinality)
, context_(parser)
, position_(position_vector)
{}

void Sequence::add_type(shared_ptr<SequenceElement> a_new_type)
{
    //create a position for the new type
    SequencePosition new_position(this, a_new_type);

    //add the new position to the sequence
    position_.push_back(new_position);
}

bool Sequence::evaluate(std::string a_token, function<void()> next_element, function<void(int32_t type, std::string message)> handle_error)
{
    int32_t subsequence_size, subsequence_position;

    evaluate_type(a_token, subsequence_size, subsequence_position);

    //move on to the next element when in the sequence
    //after the subsequence has completed
    if ( subsequence_size == subsequence_position )
        next_element();

    return true;
}

std::shared_ptr<SequenceElement> Sequence::expected_element() const
{
    if (current_position_ < position_.size())
        return position_[current_position_].item();

    else 
        return nullptr;
}

std::shared_ptr<SequenceElement> Sequence::next_expected_element() const
{
    int32_t index = next_element_position();
    if (index != -1)
        return position_[index].item();

    //when the index is out of range and the current token has no 
    else 
        return nullptr;
}

int32_t Sequence::next_element_position() const
{
    if (current_position_ < 0)
    {
        cout << "Warning: range error." << endl;
        return -1;
    }

    //if the next index is within range
    if ((current_position_+1) < position_.size())
    {
        //point to the next position
        return current_position_ + 1;
    }

    //if the sequence is at the end of it's life, 
    //current position should equal size;
    else if(!Multiplicity() && (current_position_+1) == position_.size() )
    {
        //point to the next position
        return current_position_ + 1;
    }

    //if the next index is out of range and the sequence is recurring, then return the first element.
    else if (Multiplicity())
    {
        //point to first element
        return 0;
    }

    //when the index is out of range and the current token is not repeatable.
    else 
    {
        cout << "Warning: range error." << endl;
        return -1;
    }
}

void Sequence::evaluate_type(std::string a_token, int32_t &sequence_size, int32_t &sequence_position)
{
    //todo make this a private member of sequence
    auto go_to_next_element = [&]()
    {
        int32_t index = next_element_position();
        if (index != -1)
        {
            current_position_ = index;
        }
        //when the index is out of range and the current token has no 
        else 
        {
            cout << "Warning: could not resolve next sequence element." << endl;
        }
    };

    //todo make this a private member of sequence
    auto throw_error = [&](int32_t error_code, std::string message)//lamda for throwing errors
    {
        cout << message << a_token << endl;
        context_->handle_error({error_code});
    };

    shared_ptr<SequenceElement> current_element = expected_element();
    if(!current_element)
        throw_error(UNKNOWN_ERROR, "Error: Unexpected token found: ");

    //determines wether or not the current expected token type matches or does not.
    //returns false if the evaluation is not complete.
    if (current_element && !current_element->evaluate(a_token, go_to_next_element, throw_error))
    {
        //if the expected type cannot be evaluated because the token is a repeating token,
        //evaluate the token against the next expected type. 
        //This token still may be valid if it matches the next in sequence.
        shared_ptr<SequenceElement> next_element = next_expected_element();
        if(!next_element)
            throw_error(UNKNOWN_ERROR, "Error: Unexpected token found: ");
        
        if (next_element) 
        {
            next_element->evaluate(
            a_token, 
            [&]()
            {
                go_to_next_element(); 
                go_to_next_element();
            }, 
            throw_error);
        }
    }

    //set output variables
    //give the calling context a progress report.
    sequence_size = position_.size();
    sequence_position = current_position_;
}