// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../SequenceElement.hpp"
#include <iostream>
#include "../SequencePosition.hpp"

using std::cout;
using std::endl;
using sdg::parse::SequenceElement;


void SequenceElement::assign_position(SequencePosition *position)
{
    position_.push_back(position);
}

void SequenceElement::print() const
{
    cout << "sequence element found ..." << endl;
}

bool SequenceElement::Multiplicity()
{
    return (cardinality_==Cardinality::Many);
}