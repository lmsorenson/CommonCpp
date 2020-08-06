// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../SequenceElement.hpp"
#include <iostream>
#include "../SequencePosition.hpp"

using std::cout;
using std::endl;
using sdg::parse::SequenceElement;


SequenceElement::SequenceElement(Cardinality cardinality) 
: cardinality_(cardinality)
{
}

void SequenceElement::assign_position(SequencePosition *position)
{
    element_position_ = position;
}

void SequenceElement::print() const
{
    cout << endl << "base_element" << endl << endl;
}

bool SequenceElement::HasMultiplicity() const
{
    return (cardinality_==Cardinality::Many);
}