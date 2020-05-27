// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <memory>



namespace sdg {
namespace parse {

class SequencePosition;

class SequenceElement
{
    std::vector<SequencePosition*> position_;

public:
    void assign_position(SequencePosition *position);
    void print() const;
};


}// namespace parser
}// namespace sdg