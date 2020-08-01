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

void Sequence::set_positions(vector<shared_ptr<SequencePosition>> position_vector)
{
    position_ = position_vector;
}

void Sequence::print() const
{
    cout << "Sequence: " << name_ << " position: " << current_position_ << endl;
}

void Sequence::add_element(shared_ptr<SequenceElement> a_new_type)
{
    //create a position for the new type
    shared_ptr<SequencePosition> new_position = make_shared<SequencePosition>(this, a_new_type);

    //add the new position to the sequence
    position_.push_back(new_position);
}

void Sequence::handle_error(int32_t error_code, string message) const
{
    cout << message << endl;
    context_->handle_error({error_code});
};

void Sequence::go_to_next_item()
{
    auto current_position = position_[current_position_];
    auto sequence = current_position->get_sequence();


    if(sequence)
    {
        //if the current item is a sequence and it is complete
        //or if it is a token.
        if (current_position->complete() || current_position->get_token())
            this->set_position();
        else
            sequence->set_position();
    }
    else
    {
        cout << "Warning: no next item found" << endl;
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



//matches the current token with the current expected token.  If the current expected token is repeatable
//and does not match the current token found, then also evaluate against the next expected token.
shared_ptr<TokenType> Sequence::match_token(string a_token)
{
    shared_ptr<SequenceElement> current_element = expected_element();
    if(!current_element)
        return nullptr;


    current_element->print();

    //determines wether or not the current expected token type matches or does not.
    //returns NextElementViable if the evaluation is not complete.
    MatchStatus match_status;
    auto token_type = current_element->evaluate(a_token, match_status);
    if ( match_status == MatchStatus::PositiveMatch )
    {
        if(token_type)
            return token_type;

        else
        {
            if(!current_element->HasMultiplicity())
                set_position();

            return dynamic_pointer_cast<TokenType>(current_element);
        }
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
            auto returned_element = next_element->evaluate(a_token, next_element_match_status);

            if (next_element_match_status == MatchStatus::PositiveMatch)
            {
                //if the next element is viable and has a positive match
                //move the cursor to the next element
                if ((current_position_+1) == position_.size() && !HasMultiplicity())
                    element_position_->notify_completion();
                    
                else
                    set_position();

                //if the next element is a positive match and does not recur
                //move two places forward.
                if(!next_element->HasMultiplicity())
                    element_position_->go_to_next_element();

                auto obj = dynamic_pointer_cast<TokenType>(next_element);

                if(!obj)
                    obj = dynamic_pointer_cast<TokenType>(returned_element);

                return obj;
            }
            else
            {
                return nullptr;
            }
        }
        else
        {
            return nullptr;
        }
    }
    else
        return nullptr;
}

shared_ptr<TokenType> Sequence::evaluate(const string &a_token, MatchStatus &status)
{
    auto token_type = match_token(a_token);

    if ( token_type )
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