// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../Sequence.hpp"
#include <iostream>
#include <memory>

#include "../SequencePosition.hpp"
#include "../../../Parser.hpp"

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::function;
using std::dynamic_pointer_cast;
using sdg::parse::Sequence;
using sdg::parse::SequenceElement;


Sequence::Sequence(Parser *parser, string name, Cardinality cardinality)
: SequenceElement(cardinality)
, name_(name)
, context_(parser)
, current_position_(0)
{}

void Sequence::print() const
{
    cout << "Sequence: " << name_ << endl;
}

void Sequence::add_type(shared_ptr<SequenceElement> a_new_type)
{
    //create a position for the new type
    shared_ptr<SequencePosition> new_position = make_shared<SequencePosition>(this, a_new_type);

    //add the new position to the sequence
    position_.push_back(new_position);
}

void Sequence::set_positions(vector<shared_ptr<SequencePosition>> position_vector)
{
    position_ = position_vector;
}

bool Sequence::evaluate(string a_token, function<void()> next_element, function<void(int32_t type, std::string message)> handle_error)
{
    int32_t subsequence_size, subsequence_position;

    evaluate_type(a_token, subsequence_size, subsequence_position);

    //move on to the next element when in the sequence
    //after the subsequence has completed
    if ( subsequence_size == subsequence_position )
        next_element();

    return true;
}

shared_ptr<SequenceElement> Sequence::expected_element() const
{
    if (current_position_ < position_.size())
        return position_[current_position_]->item();

    else 
        return nullptr;
}

shared_ptr<SequenceElement> Sequence::next_expected_element() const
{
    int32_t index = next_element_position();
    if (index == position_.size())
        return element_position_->next_item();

    else if (index != -1 && index != position_.size())
        return position_[index]->item();

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
    else if(!HasMultiplicity() && (current_position_+1) == position_.size() )
    {
        //position size refers to the end of a sequence
        return position_.size();
    }

    //if the next index is out of range and the sequence is recurring, then return the first element.
    else if (HasMultiplicity())
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

void Sequence::set_position()
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

void Sequence::handle_error(int32_t error_code, string message) const
{
    cout << message << endl;
    context_->handle_error({error_code});
};

void Sequence::evaluate_type(string a_token, int32_t &sequence_size, int32_t &sequence_position)
{
    shared_ptr<SequenceElement> current_element = expected_element();
    if(!current_element)
        handle_error(UNKNOWN_ERROR, "Error: Unexpected token found: ");

    //determines wether or not the current expected token type matches or does not.
    //returns false if the evaluation is not complete.
    if (current_element && !current_element->evaluate(a_token, [&](){set_position();}, [&](int32_t type, string message){handle_error(type, message);}))
    {
        //if the expected type cannot be evaluated because the token is a repeating token,
        //evaluate the token against the next expected type. 
        //This token still may be valid if it matches the next in sequence.
        shared_ptr<SequenceElement> next_element = next_expected_element();
        if(!next_element)
            handle_error(UNKNOWN_ERROR, "Error: Unexpected token found: ");
        
        if (next_element) 
        {
            next_element->evaluate(
            a_token, 
            [&]()
            {
                set_position(); 
                set_position();
            }, 
            [&](int32_t type, string message){handle_error(type, message);});
        }
    }

    //set output variables
    //give the calling context a progress report.
    sequence_size = position_.size();
    sequence_position = current_position_;
}