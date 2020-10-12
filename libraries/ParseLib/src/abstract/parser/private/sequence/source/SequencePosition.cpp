// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../SequencePosition.hpp"
#include <iostream>
#include "../SequenceElement.hpp"
#include "../Sequence.hpp"

using std::cout;
using std::endl;
using std::shared_ptr;
using std::dynamic_pointer_cast;
using sdg::parse::SequencePosition;
using sdg::parse::SequenceElement;
using sdg::parse::Sequence;
using sdg::parse::TokenType;



SequencePosition::SequencePosition(Sequence *context, shared_ptr<SequenceElement> a_element)
: sequence_(context)
, element_(a_element)
{
    element_->assign_position(this);
}

shared_ptr<SequenceElement> SequencePosition::item() const
{
    return element_;
}

shared_ptr<SequenceElement> SequencePosition::next_item() const
{
    if (sequence_)
    {
        return sequence_->next_expected_element();
    }
    else
    {
        return nullptr;
    }
}

void SequencePosition::notify_completion()
{
    is_completed = true;
    sequence_->go_to_next_item();
}

void SequencePosition::go_to_next_element()
{
    sequence_->go_to_next_item();
}

bool SequencePosition::complete()
{
    return is_completed;
}

std::shared_ptr<Sequence> SequencePosition::get_sequence()
{
    return dynamic_pointer_cast<Sequence>(element_);
}

std::shared_ptr<TokenType> SequencePosition::get_token()
{
    return dynamic_pointer_cast<TokenType>(element_);
}