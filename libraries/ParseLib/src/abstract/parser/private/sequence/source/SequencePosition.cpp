// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../SequencePosition.hpp"
#include <iostream>
#include "../SequenceElement.hpp"
#include "../Sequence.hpp"

using std::cout;
using std::endl;
using std::shared_ptr;
using sdg::parse::SequencePosition;
using sdg::parse::SequenceElement;


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