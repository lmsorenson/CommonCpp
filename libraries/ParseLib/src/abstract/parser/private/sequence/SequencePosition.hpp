// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "SequenceElement.hpp"


namespace sdg {
namespace parse {

class Sequence;

class SequencePosition
{
    Sequence *sequence_;
    SequenceElement element_;

public:
    explicit SequencePosition(Sequence *context, SequenceElement a_element);
    ~SequencePosition() = default;

    const SequenceElement * item();
};

}// namespace parser
}// namespace sdg