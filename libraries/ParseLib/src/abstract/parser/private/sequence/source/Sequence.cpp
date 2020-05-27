// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../Sequence.hpp"
#include <iostream>

#include "../SequencePosition.hpp"

using std::cout;
using std::endl;
using sdg::parse::Sequence;


void Sequence::add_type(SequenceElement a_new_type)
{
    //create a position for the new type
    SequencePosition new_position(this, a_new_type);

    //add the new position to the sequence
    position_.push_back(new_position);
}

void Sequence::evaluate_type(std::string token)
{
    if (current_position_ < position_.size() )
    {
        auto position = position_[current_position_++];
        auto item = position.item();
        item->print();
    }
    else
    {
        cout << "no item" << endl;
    }
    
}