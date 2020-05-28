// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../Sequence.hpp"
#include <iostream>

#include "../SequencePosition.hpp"
#include "../../../Parser.hpp"

using std::cout;
using std::endl;
using std::shared_ptr;
using std::dynamic_pointer_cast;
using sdg::parse::Sequence;


void Sequence::add_type(shared_ptr<SequenceElement> a_new_type)
{
    //create a position for the new type
    SequencePosition new_position(this, a_new_type);

    //add the new position to the sequence
    position_.push_back(new_position);
}

void Sequence::evaluate_type(std::string a_token, int32_t &sequence_size, int32_t &sequence_position)
{
    if ( current_position_ < position_.size() )
    {
        SequencePosition position = position_[current_position_];
        
        shared_ptr<Sequence> local_sequence;
        shared_ptr<TokenType> local_type;

        if( (local_sequence = dynamic_pointer_cast<Sequence>(position.item())) )
        {
            int32_t subsequence_size, subsequence_position;

            local_sequence->evaluate_type(a_token, subsequence_size, subsequence_position);

            //move on to the next element when in the sequence
            //after the subsequence has completed
            if ( subsequence_size == subsequence_position )
            {
                current_position_++;

                //todo -- for recurring sequences go back to the beginning of the sequence and repeat until the next token is found.
            }
        }
        else if( (local_type = dynamic_pointer_cast<TokenType>(position.item())) )
        {
            //if the token matches
            if ( (local_type->classify(a_token) && !local_type->Multiplicity()) )
            {
                //move to the next item.
                current_position_++;
            }
            //if the token does not match
            else
            {
                cout << "Error: Sequence position has unexpected type." << endl;
                context_->handle_error({UNKNOWN_ERROR});
            }
        }
        else
        {
            cout << "Error: Sequence position has unexpected type." << endl;
            context_->handle_error({UNKNOWN_ERROR});
        }
    }
    else
    {
        cout << "Error: Unexpected token found: " << a_token << endl;
        context_->handle_error({UNKNOWN_ERROR});
    }

    //set output variables
    //give the calling context a progress report.
    sequence_size = position_.size();
    sequence_position = current_position_;
}