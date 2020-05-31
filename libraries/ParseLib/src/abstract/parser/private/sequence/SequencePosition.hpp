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
    std::shared_ptr<SequenceElement> element_;

public:
    explicit SequencePosition(Sequence *context, std::shared_ptr<SequenceElement> a_element);
    ~SequencePosition() = default;
    
    std::shared_ptr<SequenceElement> next_item() const;
    std::shared_ptr<SequenceElement> item() const;
};

}// namespace parser
}// namespace sdg