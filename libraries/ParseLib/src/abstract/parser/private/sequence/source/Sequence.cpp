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
using sdg::parse::TokenType;
using sdg::parse::MatchStatus;

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

void Sequence::add_element(shared_ptr<SequenceElement> a_new_type)
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

shared_ptr<TokenType> Sequence::evaluate(string a_token, function<void()> next_element, function<void(int32_t type, std::string message)> handle_error, MatchStatus &status)
{
    int32_t subsequence_size, subsequence_position;

    auto token_type = match_token(a_token, subsequence_size, subsequence_position);

    //move on to the next element when in the sequence
    //after the subsequence has completed
    if ( subsequence_size == subsequence_position )
        next_element();

    if(token_type)
    {
        status = MatchStatus::PositiveMatch;
        return token_type;
    }
    else
    {
        status = MatchStatus::Unknown;
        return nullptr;
    }
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

//matches the current token with the current expected token.  If the current expected token is repeatable
//and does not match the current token found, then also evaluate against the next expected token.
shared_ptr<TokenType> Sequence::match_token(string a_token, int32_t &sequence_size, int32_t &sequence_position)
{
    shared_ptr<SequenceElement> current_element = expected_element();
    if(!current_element)
    {
        handle_error(UNKNOWN_ERROR, "Error: Unexpected token found: ");
        return nullptr;
    }

    //determines wether or not the current expected token type matches or does not.
    //returns false if the evaluation is not complete.
    MatchStatus match_status;
    auto token_type = current_element->evaluate(a_token, [&](){set_position();}, [&](int32_t type, string message){handle_error(type, message);}, match_status);
    if ( match_status == MatchStatus::PositiveMatch )
    {
        if(token_type)
            return token_type;
        else
            return dynamic_pointer_cast<TokenType>(current_element);
    }
    else if ( match_status == MatchStatus::NextElementViable )
    {
        //if the expected type cannot be evaluated because the token is a repeating token,
        //evaluate the token against the next expected type. 
        //This token still may be valid if it matches the next in sequence.
        shared_ptr<SequenceElement> next_element = next_expected_element();
        if (next_element) 
        {
            MatchStatus next_element_match_status;
            next_element->evaluate(a_token, [&](){set_position(); set_position();}, [&](int32_t type, string message){handle_error(type, message);}, next_element_match_status);
            if (next_element_match_status == MatchStatus::PositiveMatch)
                return dynamic_pointer_cast<TokenType>(next_element);

            else
                return nullptr;
        }
        else
        {
            handle_error(UNKNOWN_ERROR, "Error: Unexpected token found: ");
            return nullptr;
        }
    }
    else
        return nullptr;

    //give the calling context a progress report.
    sequence_size = position_.size();
    sequence_position = current_position_;
}